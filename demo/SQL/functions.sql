-- SQL拥有很多可用于计数和计算的内建函数

SELECT AVG(age) AS age_avg FROM student -- 返回数值列age的平均值
SELECT COUNT(*) AS nums FROM student -- 返回表中的记录数
SELECT MAX(age) AS age_max FROM student -- 返回指定列age的最大值
SELECT MIN(age) AS age_min FROM student -- 返回指定列age的最小值
SELECT SUM(age) AS age_sum FROM student -- 返回数值列age的总数
SELECT UPPER(sex) AS sex_ucase FROM student -- 把字段sex的值转换为大写：UPPER(SQL Server)/UCASE
SELECT LOWER(name) AS name_lcase FROM student -- 把字段name的值转换为小写: LOWER(SQL Server)/LCASE
SELECT LEN(name) AS len_name FROM student -- 返回name段中值的长度
