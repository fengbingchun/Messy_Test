/*
SELECT：用于从数据库中查询数据，结果被存储在一个结果表中，称为结果集
SELECT column_name(s) FROM table_name WHERE condition ORDER BY column_name [ASC|DESC]
WHERE：用于指定筛选条件
ORDER BY：用于对结果集进行排序：ASC:升序(默认)；DESC:降序
GROUP BY：用于将结果集按一列或多列进行分组
HAVING：用于对分组后的结果集进行筛选
JOIN：用于将两个或多个表的记录结合起来
DISTINCT：用于返回唯一不同的值: SELECT DISTINCT column1, column2, ... FROM table_name
BETWEEN：选取介于两个值之间的数据范围内的值，这些值可以是数值、文本或者日期
LIKE：用于在WHERE子句中进行模糊查询，通常与%(匹配任意字符(包括零个字符))和_(匹配单个字符)通配符一起使用
IN：允许在WHERE子句中规定多个值
*/

SELECT * FROM student -- 显示表student的所有数据
SELECT name, age FROM student -- 仅显示name和age列数据
SELECT * FROM student WHERE age > 20 ORDER BY age DESC -- 显示age>20的所有数据，并按降序排列
SELECT DISTINCT sex FROM student -- 最多显示2条数据
SELECT * FROM student WHERE sex='男' -- 显示表student中sex为男的数据
SELECT * FROM student WHERE age >= 21 AND age < 100 -- 显示age>=21并且age<100的所有数据
SELECT * FROM student WHERE age BETWEEN 21 AND 100 -- 显示age>=21并且age<=100的所有数据
SELECT * FROM student WHERE name LIKE '小%' -- 显示name是小开头的所有数据
SELECT * FROM student WHERE name NOT LIKE '小%' -- 显示name不是小开头的所有数据
SELECT * FROM student WHERE age IN(10, 20) -- 显示age为10和20的所有数据
