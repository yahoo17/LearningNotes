### 集合操作

#### 并集

nFind courses that ran in Fall 2009 or in Spring 2010

```
select course_id from section where semester = 'Fall' and year = 2009
 union
select course_id from section where semester = 'Spring' and year = 2010

```



#### 交集1

nFind courses offered in Fall 2009 and in Spring 2010

```
select distinct course_id
from section
where semester = 'Fall' and year= 2009 and            course_id   in (select course_id
                                        from section
                                        where semester = 'Spring' and year= 2010);

```

#### 交集2

用你exists

```
select course_id
    -> from section as S
    -> where semester='fall' and year=2009 and exists (select * from section as T where semester='spring' and year=2010 and s.course_id=t.course_id);
```



#### 差集2

​     Find courses that ran in Fall 2009 but not in Spring 2010  

```
 select distinct course_id
    -> from section
    -> where semester="fall" and year=2009 and course_id not in(select distinct course_id from section where semester="spring" and year=2010);
```

#### 差集1

**Find the salaries of all instructors that are less than the largest salary.**

```
select distinct T.salary
from *instructor* as *T, instructor* as  S

*where*   *T.salary* *<* *S.salary* 
```



**Find all the salaries of all instructors**

```
**select distinct** *salary
\* **from** *instructor*
```



**Find the largest salary of all instructors.**

```
 (**select** “second query” )
 **except
**  (**select** “first query”)

//_______
select salary from instructor where salary not in (select distinct a.salary from instructor a,instructor b where a.salary<b.salary); 
```

### 集合函数

**Find the average salary of instructors in the Computer Science department** 

```
**select** **avg** (*salary*)
 **from** *instructor
\* **where** *dept_name*= 'Comp. Sci.';
```



**Find the total number of instructors who teach a course in the Spring 2010 semester**

```
**select count** (**distinct** *ID*)
 **from** *teaches
\* **where** *semester* = 'Spring' **and** *year* = 2010
```



**Find the number of tuples in the *course* relation**

```
**select count** (*)
 **from** *course*;
```

**把每个学院的平均收入打出来**

```
select dept_name,avg(Salary)
    -> from instructor
    -> group by dept_name;
    -> 
```

**Find the names and average salaries of all departments whose average salary is greater than 42000**

*Note: predicates in the* **having** *clause are applied after the formation of groups whereas predicates in the* **where** *clause are applied before forming groups*

```
select dept_name, avg (salary)
from instructor
group by dept_name
having avg (salary) > 42000;

```

#### 综合

nFind the total number of (distinct) students who have taken course sections taught by the instructor with *ID* 10101

**找到参加了教工号10101老师开的课的学生数量**

     *Note: Above query can be written in a much simpler manner. 

   The formulation above is simply to illustrate SQL features.*  

```
select count (distinct ID)
from takes
where (course_id, sec_id, semester, year) in                                 (select course_id, sec_id, semester, year
                                 from teaches
                                 where teaches.ID= 10101);

```

**Find names of instructors with salary greater than that of some (at least one) instructor in the Biology department.**

 Same query using > **some** clause

```
select name
from instructor
where salary > some (select salary
                                     from instructor
                                     where dept_name = 'Biology');

```



```
select distinct T.name
from instructor as T, instructor as S
where T.salary > S.salary and S.dept_name = 'Biology';

```

找到比生物系所有老师收入高的老师的收入和name

```
select name, salary
    -> from instructor
    -> where salary>all(select salary from instructor where dept_name="biology");
```

#### NOT EXISTS



#### Update

nSets *tot_creds* to null for students who have not taken any course

```
update student S

set tot_cred=null

where S.ID not in （select ID from takes）；
```



#### left outer join | right outer join |full outer join

![1586328253464](Mysql.assets/1586328253464.png)

保留左边的course_id 

