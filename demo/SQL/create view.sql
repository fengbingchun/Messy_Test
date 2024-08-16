/*
CREATE VIEW: 创建视图。视图中的字段就是来自一个或多个数据库中的真实的表中的字段
CREATE VIEW view_name AS SELECT column1, column2, ... FROM table_name WHERE condition
*/

CREATE VIEW big_age AS SELECT id, name, sex, age FROM student WHERE age>20
