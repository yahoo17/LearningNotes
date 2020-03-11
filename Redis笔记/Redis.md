# Redis

## Redis的入门应用

### Redis是key-value型数据库

### Redis 里的单行命令都是原子的 是为了同时有多个用户对同一个数据修改

### string

- set key value

	- 子主题 1

		-     SET server:name "fido"
		-     GET server:name => "fido"
		-     EXISTS server:name => 1
		-     EXISTS server:blabla => 0
		-     SET connections 10
		-     INCR connections => 11
		-     INCR connections => 12
		-     DEL connections
		-     INCR connections => 1
		- It is also possible to increment the number contained inside a key by a specific amount:
		-     INCRBY connections 100 => 101
		- And there are similar commands in order to decrement the value of the key.
		-     DECR connections => 100
		-     DECRBY connections 10 => 90

- get key
- exists key
- DEL key
- EXPIRE key 100

	- 100秒后删除
	- TTL key 

		- 显示还有几秒删除
		- 只要set key 一次 之前的计时失效 TTL key 返回-1
		- 返回-2说明计时过了 这东西被删了

	- PERSIST key

		- 让这个计时结束

			- 永久保存

- INCR key

	- INCRBY key 100

- DECR key

	- DECRBY key 100

- 不能简单的get  key \ value=value+1 \set key value 

### list

- 对头尾操作较快 且 有序号的
- lpush friend "yanhao" 

	- rpush friend "yanhao"
	- lpush friend 1 2 3 4 
	- 执行顺序是

		- lpush friend 1
		- lpush friend 2
		- lpush friend 3
		- lpush friend 4

	- 所以结果是 4 3 2 1

- lrange friend 0 -1

	- 切片
	- example

		- LRANGE friends 0 -1 => 1) "Sam", 2) "Alice", 3) "Bob" 
		-     LRANGE friends 0 1 => 1) "Sam", 2) "Alice"
		-     LRANGE friends 1 2 => 1) "Alice", 2) "Bob"
		- lrange friend 0 10

			-  1) "Sam", 2) "Alice", 3) "Bob" 

		- lrange friend -3 -1

			-  1) "Sam", 2) "Alice", 3) "Bob" 

- lset friend 0 "yanhao"

	- 把friend这个list里面的第0个元素改成"yanhao"

- lpop friend

	- rpop friend
	- 子主题 2

- llen

### set

- sadd setname "yanhao"

	- return 0

		- 没加成功,因为本来就有这个key了

	- return 1

		- 加成功了

- sismember setname "yanhao"
- smembers friend
- sincr
- sdecr
- srem  friend "yanhao"

	- return 0
	- return 1

- srandmeber friend  2

	- 随机返回数据成员

- spop

	- 随机删

- sunion set1 set2

### sorted set

- 在set的同时加上一个用来排序的东西
- ZADD fruit 1 apple
- ZADD fruit 2 banano
- Zrange fruit 0 1

	- 切片

### hashes

- hset user:37 name "yanhao"
- hgetall user:37  
- hmset user:37 name "yanhao" age 17

	- 同时设置多个

- hget user:37 name
- hincrby user:37 name 2

	- name会加2

- hdel

## 分支主题 2

## 分支主题 3

*XMind: ZEN - Trial Version*