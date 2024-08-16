/*
INSERT INTO：用于向表中插入新数据
INSERT INTO table_name(column1, column2, ...) VALUES(value1, value2, ...)
*/

-- INSERT INTO语句可以有两种编写形式
-- 第一种形式无需指定要插入数据的列名，只需提供被插入的值即可
INSERT INTO student VALUES(1013, '小王', '女', 35, 2016-10-15)
INSERT INTO student VALUES(1014, 'Lucy', 'woman', 5, '2020-11-25 10:10:10')

-- 第二种形式需要指定列名及被插入的值
INSERT INTO student(id, name, sex, age) VALUES(1020, 'Lucy', '女', 10)
