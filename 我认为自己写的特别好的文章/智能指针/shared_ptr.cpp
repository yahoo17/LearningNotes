template <class _Ty>
class shared_ptr : public _Ptr_base<_Ty> { // class for reference counted resource management
private:
    using _Mybase = _Ptr_base<_Ty>;

public:
    using typename _Mybase::element_type;

#if _HAS_CXX17
    using weak_type = weak_ptr<_Ty>;
#endif // _HAS_CXX17

    constexpr shared_ptr() noexcept {} // construct empty shared_ptr

    constexpr shared_ptr(nullptr_t) noexcept {} // construct empty shared_ptr

    template <class _Ux,
        enable_if_t<conjunction_v<conditional_t<is_array_v<_Ty>, _Can_array_delete<_Ux>, _Can_scalar_delete<_Ux>>,
        _SP_convertible<_Ux, _Ty>>,
        int> = 0>
        explicit shared_ptr(_Ux* _Px) { // construct shared_ptr object that owns _Px
#if _HAS_IF_CONSTEXPR
        if constexpr (is_array_v<_Ty>) {
            _Setpd(_Px, default_delete<_Ux[]>{});
        }
        else {
            _Temporary_owner<_Ux> _Owner(_Px);
            _Set_ptr_rep_and_enable_shared(_Owner._Ptr, new _Ref_count<_Ux>(_Owner._Ptr));
            _Owner._Ptr = nullptr;
        }
#else // ^^^ _HAS_IF_CONSTEXPR // !_HAS_IF_CONSTEXPR vvv
        _Setp(_Px, is_array<_Ty>{});
#endif // _HAS_IF_CONSTEXPR
    }

    template <class _Ux, class _Dx,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, _Ux*&>,
        _SP_convertible<_Ux, _Ty>>,
        int> = 0>
        shared_ptr(_Ux* _Px, _Dx _Dt) { // construct with _Px, deleter
        _Setpd(_Px, _STD move(_Dt));
    }

    template <class _Ux, class _Dx, class _Alloc,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, _Ux*&>,
        _SP_convertible<_Ux, _Ty>>,
        int> = 0>
        shared_ptr(_Ux* _Px, _Dx _Dt, _Alloc _Ax) { // construct with _Px, deleter, allocator
        _Setpda(_Px, _STD move(_Dt), _Ax);
    }

    template <class _Dx,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, nullptr_t&>>, int> = 0>
        shared_ptr(nullptr_t, _Dx _Dt) { // construct with nullptr, deleter
        _Setpd(nullptr, _STD move(_Dt));
    }

    template <class _Dx, class _Alloc,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, nullptr_t&>>, int> = 0>
        shared_ptr(nullptr_t, _Dx _Dt, _Alloc _Ax) { // construct with nullptr, deleter, allocator
        _Setpda(nullptr, _STD move(_Dt), _Ax);
    }

    template <class _Ty2>
    shared_ptr(const shared_ptr<_Ty2>& _Right, element_type* _Px) noexcept {
        // construct shared_ptr object that aliases _Right
        this->_Alias_construct_from(_Right, _Px);
    }

    template <class _Ty2>
    shared_ptr(shared_ptr<_Ty2>&& _Right, element_type* _Px) noexcept {
        // move construct shared_ptr object that aliases _Right
        this->_Alias_move_construct_from(_STD move(_Right), _Px);
    }

    shared_ptr(const shared_ptr& _Other) noexcept { // construct shared_ptr object that owns same resource as _Other
        this->_Copy_construct_from(_Other);
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    shared_ptr(const shared_ptr<_Ty2>& _Other) noexcept {
        // construct shared_ptr object that owns same resource as _Other
        this->_Copy_construct_from(_Other);
    }

    shared_ptr(shared_ptr&& _Right) noexcept { // construct shared_ptr object that takes resource from _Right
        this->_Move_construct_from(_STD move(_Right));
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    shared_ptr(shared_ptr<_Ty2>&& _Right) noexcept { // construct shared_ptr object that takes resource from _Right
        this->_Move_construct_from(_STD move(_Right));
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    explicit shared_ptr(const weak_ptr<_Ty2>& _Other) { // construct shared_ptr object that owns resource *_Other
        if (!this->_Construct_from_weak(_Other)) {
            _Throw_bad_weak_ptr();
        }
    }

#if _HAS_AUTO_PTR_ETC
    template <class _Ty2, enable_if_t<is_convertible_v<_Ty2*, _Ty*>, int> = 0>
    shared_ptr(auto_ptr<_Ty2>&& _Other) { // construct shared_ptr object that owns *_Other.get()
        _Ty2* _Px = _Other.get();
        _Set_ptr_rep_and_enable_shared(_Px, new _Ref_count<_Ty2>(_Px));
        _Other.release();
    }
#endif // _HAS_AUTO_PTR_ETC

    template <class _Ux, class _Dx,
        enable_if_t<conjunction_v<_SP_pointer_compatible<_Ux, _Ty>,
        is_convertible<typename unique_ptr<_Ux, _Dx>::pointer, element_type*>>,
        int> = 0>
        shared_ptr(unique_ptr<_Ux, _Dx>&& _Other) {
        using _Fancy_t = typename unique_ptr<_Ux, _Dx>::pointer;
        using _Raw_t = typename unique_ptr<_Ux, _Dx>::element_type*;
        using _Deleter_t = conditional_t<is_reference_v<_Dx>, decltype(_STD ref(_Other.get_deleter())), _Dx>;

        const _Fancy_t _Fancy = _Other.get();

        if (_Fancy) {
            const _Raw_t _Raw = _Fancy;
            const auto _Rx = new _Ref_count_resource<_Fancy_t, _Deleter_t>(_Fancy, _Other.get_deleter());
            _Set_ptr_rep_and_enable_shared(_Raw, _Rx);
            _Other.release();
        }
    }

    ~shared_ptr() noexcept { // release resource
        this->_Decref();
    }

    shared_ptr& operator=(const shared_ptr& _Right) noexcept {
        shared_ptr(_Right).swap(*this);
        return *this;
    }

    template <class _Ty2>
    shared_ptr& operator=(const shared_ptr<_Ty2>& _Right) noexcept {
        shared_ptr(_Right).swap(*this);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& _Right) noexcept { // take resource from _Right
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

    template <class _Ty2>
    shared_ptr& operator=(shared_ptr<_Ty2>&& _Right) noexcept { // take resource from _Right
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

#if _HAS_AUTO_PTR_ETC
    template <class _Ty2>
    shared_ptr& operator=(auto_ptr<_Ty2>&& _Right) {
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }
#endif // _HAS_AUTO_PTR_ETC

    template <class _Ux, class _Dx>
    shared_ptr& operator=(unique_ptr<_Ux, _Dx>&& _Right) { // move from unique_ptr
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

    void swap(shared_ptr& _Other) noexcept {
        this->_Swap(_Other);
    }

    void reset() noexcept { // release resource and convert to empty shared_ptr object
        shared_ptr().swap(*this);
    }

    template <class _Ux>
    void reset(_Ux* _Px) { // release, take ownership of _Px
        shared_ptr(_Px).swap(*this);
    }

    template <class _Ux, class _Dx>
    void reset(_Ux* _Px, _Dx _Dt) { // release, take ownership of _Px, with deleter _Dt
        shared_ptr(_Px, _Dt).swap(*this);
    }

    template <class _Ux, class _Dx, class _Alloc>
    void reset(_Ux* _Px, _Dx _Dt, _Alloc _Ax) { // release, take ownership of _Px, with deleter _Dt, allocator _Ax
        shared_ptr(_Px, _Dt, _Ax).swap(*this);
    }

    using _Mybase::get;

    template <class _Ty2 = _Ty, enable_if_t<!disjunction_v<is_array<_Ty2>, is_void<_Ty2>>, int> = 0>
    _NODISCARD _Ty2& operator*() const noexcept {
        return *get();
    }

    template <class _Ty2 = _Ty, enable_if_t<!is_array_v<_Ty2>, int> = 0>
    _NODISCARD _Ty2* operator->() const noexcept {
        return get();
    }

    template <class _Ty2 = _Ty, class _Elem = element_type, enable_if_t<is_array_v<_Ty2>, int> = 0>
    _NODISCARD _Elem& operator[](ptrdiff_t _Idx) const noexcept /* strengthened */ {
        return get()[_Idx];
    }

    _NODISCARD _CXX17_DEPRECATE_SHARED_PTR_UNIQUE bool unique() const noexcept {
        // return true if no other shared_ptr object owns this resource
        return this->use_count() == 1;
    }

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }

private:
#if !_HAS_IF_CONSTEXPR
    template <class _Ux>
    void _Setp(_Ux* _Px, true_type) { // take ownership of _Px
        _Setpd(_Px, default_delete<_Ux[]>{});
    }

    template <class _Ux>
    void _Setp(_Ux* const _Px, false_type) { // take ownership of _Px
        _Temporary_owner<_Ux> _Owner(_Px);
        _Set_ptr_rep_and_enable_shared(_Owner._Ptr, new _Ref_count<_Ux>(_Owner._Ptr));
        _Owner._Ptr = nullptr;
    }
#endif // !_HAS_IF_CONSTEXPR

    template <class _UxptrOrNullptr, class _Dx>
    void _Setpd(const _UxptrOrNullptr _Px, _Dx _Dt) { // take ownership of _Px, deleter _Dt
        _Temporary_owner_del<_UxptrOrNullptr, _Dx> _Owner(_Px, _Dt);
        _Set_ptr_rep_and_enable_shared(
            _Owner._Ptr, new _Ref_count_resource<_UxptrOrNullptr, _Dx>(_Owner._Ptr, _STD move(_Dt)));
        _Owner._Call_deleter = false;
    }

    template <class _UxptrOrNullptr, class _Dx, class _Alloc>
    void _Setpda(const _UxptrOrNullptr _Px, _Dx _Dt, _Alloc _Ax) { // take ownership of _Px, deleter _Dt, allocator _Ax
        using _Alref_alloc = _Rebind_alloc_t<_Alloc, _Ref_count_resource_alloc<_UxptrOrNullptr, _Dx, _Alloc>>;

        _Temporary_owner_del<_UxptrOrNullptr, _Dx> _Owner(_Px, _Dt);
        _Alref_alloc _Alref(_Ax);
        _Alloc_construct_ptr<_Alref_alloc> _Constructor(_Alref);
        _Constructor._Allocate();
        _Construct_in_place(*_Constructor._Ptr, _Owner._Ptr, _STD move(_Dt), _Ax);
        _Set_ptr_rep_and_enable_shared(_Owner._Ptr, _Unfancy(_Constructor._Ptr));
        _Constructor._Ptr = nullptr;
        _Owner._Call_deleter = false;
    }

    template <class _Ty0, class... _Types>
    friend shared_ptr<_Ty0> make_shared(_Types&&... _Args);

    template <class _Ty0, class _Alloc, class... _Types>
    friend shared_ptr<_Ty0> allocate_shared(const _Alloc& _Al_arg, _Types&&... _Args);

    template <class _Ux>
    void _Set_ptr_rep_and_enable_shared(_Ux* const _Px, _Ref_count_base* const _Rx) noexcept { // take ownership of _Px
        this->_Ptr = _Px;
        this->_Rep = _Rx;
#if _HAS_IF_CONSTEXPR
        if constexpr (conjunction_v<negation<is_array<_Ty>>, negation<is_volatile<_Ux>>, _Can_enable_shared<_Ux>>) {
            if (_Px && _Px->_Wptr.expired()) {
                _Px->_Wptr = shared_ptr<remove_cv_t<_Ux>>(*this, const_cast<remove_cv_t<_Ux>*>(_Px));
            }
        }
#else // ^^^ _HAS_IF_CONSTEXPR // !_HAS_IF_CONSTEXPR vvv
        _Enable_shared_from_this1(*this, _Px,
            bool_constant<
            conjunction_v<negation<is_array<_Ty>>, negation<is_volatile<_Ux>>, _Can_enable_shared<_Ux>>>{});
#endif // _HAS_IF_CONSTEXPR
    }

    void _Set_ptr_rep_and_enable_shared(nullptr_t, _Ref_count_base* const _Rx) noexcept { // take ownership of nullptr
        this->_Ptr = nullptr;
        this->_Rep = _Rx;
    }
};

#if _HAS_CXX17
template <class _Ty>
shared_ptr(weak_ptr<_Ty>)->shared_ptr<_Ty>;

template <class _Ty, class _Dx>
shared_ptr(unique_ptr<_Ty, _Dx>)->shared_ptr<_Ty>;
#endif // _HAS_CXX17

template <class _Ty1, class _Ty2>
_NODISCARD bool operator==(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() == _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator!=(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() != _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator<(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() < _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator>=(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() >= _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator>(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() > _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator<=(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() <= _Right.get();
}

template <class _Ty>
_NODISCARD bool operator==(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() == nullptr;
}

template <class _Ty>
_NODISCARD bool operator==(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return nullptr == _Right.get();
}

template <class _Ty>
_NODISCARD bool operator!=(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() != nullptr;
}

template <class _Ty>
_NODISCARD bool operator!=(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return nullptr != _Right.get();
}

template <class _Ty>
_NODISCARD bool operator<(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() < static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator<(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) < _Right.get();
}

template <class _Ty>
_NODISCARD bool operator>=(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() >= static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator>=(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) >= _Right.get();
}

template <class _Ty>
_NODISCARD bool operator>(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() > static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator>(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) > _Right.get();
}

template <class _Ty>
_NODISCARD bool operator<=(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() <= static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator<=(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) <= _Right.get();
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Out, const shared_ptr<_Ty>& _Px) {
    // write contained pointer to stream
    return _Out << _Px.get();
}

template <class _Ty>
void swap(shared_ptr<_Ty>& _Left, shared_ptr<_Ty>& _Right) noexcept {
    _Left.swap(_Right);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> static_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // static_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = static_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_Other, _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> static_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // static_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = static_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> const_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // const_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = const_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_Other, _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> const_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // const_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = const_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> reinterpret_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // reinterpret_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = reinterpret_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_Other, _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> reinterpret_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // reinterpret_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = reinterpret_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
}

#ifdef _CPPRTTI
template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> dynamic_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // dynamic_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = dynamic_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());

    if (_Ptr) {
        return shared_ptr<_Ty1>(_Other, _Ptr);
    }

    return shared_ptr<_Ty1>();
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> dynamic_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // dynamic_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = dynamic_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());

    if (_Ptr) {
        return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
    }

    return shared_ptr<_Ty1>();
}
#else // _CPPRTTI
template <class _Ty1, class _Ty2>
shared_ptr<_Ty1> dynamic_pointer_cast(const shared_ptr<_Ty2>&) noexcept = delete; // requires /GR option
template <class _Ty1, class _Ty2>
shared_ptr<_Ty1> dynamic_pointer_cast(shared_ptr<_Ty2>&&) noexcept = delete; // requires /GR option
#endif // _CPPRTTI

#if _HAS_STATIC_RTTI
template <class _Dx, class _Ty>
_NODISCARD _Dx* get_deleter(const shared_ptr<_Ty>& _Sx) noexcept {
    // return pointer to shared_ptr's deleter object if its type is _Dx
    if (_Sx._Rep) {
        return static_cast<_Dx*>(_Sx._Rep->_Get_deleter(typeid(_Dx)));
    }

    return nullptr;
}
#else // _HAS_STATIC_RTTI
template <class _Dx, class _Ty>
_Dx* get_deleter(const shared_ptr<_Ty>&) noexcept = delete; // requires static RTTI
#endif // _HAS_STATIC_RTTI

// _Ref_count_obj is an ABI zombie name

// CLASS TEMPLATE _Ref_count_obj2
template <class _Ty>
class _Ref_count_obj2 : public _Ref_count_base { // handle reference counting for object in control block, no allocator
public:
    template <class... _Types>
    explicit _Ref_count_obj2(_Types&&... _Args) : _Ref_count_base() {
        _Construct_in_place(_Storage._Value, _STD forward<_Types>(_Args)...);
    }

    ~_Ref_count_obj2() {
        // nothing to do, _Storage._Value was already destroyed in _Destroy
    }

    union {
        _Wrap<_Ty> _Storage;
    };

private:
    virtual void _Destroy() noexcept override { // destroy managed resource
        _Destroy_in_place(_Storage._Value);
    }

    virtual void _Delete_this() noexcept override { // destroy self
        delete this;
    }
};

// CLASS TEMPLATE _Ebco_base
template <class _Ty,
    bool = is_empty_v<_Ty> && !is_final_v<_Ty>>
    class _Ebco_base : private _Ty { // Empty Base Class Optimization, active
    private:
        using _Mybase = _Ty; // for visualization

    protected:
        template <class _Other, enable_if_t<!is_same_v<_Remove_cvref_t<_Other>, _Ebco_base>, int> = 0>
        explicit _Ebco_base(_Other&& _Val) noexcept(is_nothrow_constructible_v<_Ty, _Other>)
            : _Ty(_STD forward<_Other>(_Val)) {}

        _Ty& _Get_val() noexcept {
            return *this;
        }

        const _Ty& _Get_val() const noexcept {
            return *this;
        }
};

template <class _Ty>
class _Ebco_base<_Ty, false> { // Empty Base Class Optimization, inactive
private:
    _Ty _Myval;

protected:
    template <class _Other, enable_if_t<!is_same_v<_Remove_cvref_t<_Other>, _Ebco_base>, int> = 0>
    explicit _Ebco_base(_Other&& _Val) noexcept(is_nothrow_constructible_v<_Ty, _Other>)
        : _Myval(_STD forward<_Other>(_Val)) {}

    _Ty& _Get_val() noexcept {
        return _Myval;
    }

    const _Ty& _Get_val() const noexcept {
        return _Myval;
    }
};

// _Ref_count_obj_alloc is an ABI zombie name

// CLASS TEMPLATE _Ref_count_obj_alloc2
template <class _Ty, class _Alloc>
class __declspec(empty_bases)_Ref_count_obj_alloc2 : public _Ebco_base<_Alloc>, public _Ref_count_base {
    // handle reference counting for object in control block, allocator
public:
    template <class... _Types>
    explicit _Ref_count_obj_alloc2(const _Alloc& _Al_arg, _Types&&... _Args)
        : _Ebco_base<_Alloc>(_Al_arg), _Ref_count_base() {
        _Maybe_rebind_alloc_t<_Alloc, _Ty> _Alty(this->_Get_val());
        allocator_traits<_Rebind_alloc_t<_Alloc, _Ty>>::construct(
            _Alty, _STD addressof(_Storage._Value), _STD forward<_Types>(_Args)...);
    }

    union {
        _Wrap<_Ty> _Storage;
    };

private:
    ~_Ref_count_obj_alloc2() {
        // nothing to do; _Storage._Value already destroyed by _Destroy()
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        _Maybe_rebind_alloc_t<_Alloc, _Ty> _Alty(this->_Get_val());
        allocator_traits<_Rebind_alloc_t<_Alloc, _Ty>>::destroy(_Alty, _STD addressof(_Storage._Value));
    }

    virtual void _Delete_this() noexcept override { // destroy self
        _Rebind_alloc_t<_Alloc, _Ref_count_obj_alloc2> _Al(this->_Get_val());
        this->~_Ref_count_obj_alloc2();
        _Deallocate_plain(_Al, this);
    }
};

// FUNCTION TEMPLATE make_shared
template <class _Ty, class... _Types>
_NODISCARD shared_ptr<_Ty> make_shared(_Types&&... _Args) { // make a shared_ptr
    const auto _Rx = new _Ref_count_obj2<_Ty>(_STD forward<_Types>(_Args)...);
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_STD addressof(_Rx->_Storage._Value), _Rx);
    return _Ret;
}

// FUNCTION TEMPLATE allocate_shared
template <class _Ty, class _Alloc, class... _Types>
_NODISCARD shared_ptr<_Ty> allocate_shared(const _Alloc& _Al, _Types&&... _Args) { // make a shared_ptr
    // Note: As of 2019-05-28, this implements the proposed resolution of LWG 3210 (which controls whether
    // allocator::construct sees T or const T when _Ty is const qualified)
    using _Refoa = _Ref_count_obj_alloc2<remove_cv_t<_Ty>, _Alloc>;
    using _Alblock = _Rebind_alloc_t<_Alloc, _Refoa>;
    _Alblock _Rebound(_Al);
    _Alloc_construct_ptr<_Alblock> _Constructor{ _Rebound };
    _Constructor._Allocate();
    _Construct_in_place(*_Constructor._Ptr, _Al, _STD forward<_Types>(_Args)...);
    shared_ptr<_Ty> _Ret;
    const auto _Ptr = reinterpret_cast<_Ty*>(_STD addressof(_Constructor._Ptr->_Storage._Value));
    _Ret._Set_ptr_rep_and_enable_shared(_Ptr, _Unfancy(_Constructor._Release()));
    return _Ret;
}