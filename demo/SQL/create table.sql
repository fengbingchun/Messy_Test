/*
CREATE TABLE：用于创建新的数据库表
CREATE TABLE table_name (
    column1 data_type constraint,
    column2 data_type constraint,
    ...
)

约束(constraint)：
    NOT NULL：指示某列不能存储NULL值，在默认的情况下，表的列接受NULL值
    UNIQUE：保证某列的每行必须有唯一的值
    PRIMARY KEY：NOT NULL和UNIQUE的结合，确保某列(或两个列多个列的结合)有唯一标识。每个表可以有多个UNIQUE约束，但是每个表只能有一个PRIMARY KEY约束
    FOREIGN KEY：用于预防破坏表之间连接的行为。一个表中的FOREIGN KEY(外键)指向另一个表中的PRIMARY KEY(主键)
    CHECK：保证列中的值符合指定的条件
    DEFAULT：规定没有给列赋值时的默认值
*/

/*
CREATE TABLE teacher (
    id int,
    name char(32),
    addr char(64),
    age int,
    sex char(8)
)
*/

CREATE TABLE teacher2 (
    id int NOT NULL PRIMARY KEY CHECK(id>1000),
    name char(32) NOT NULL UNIQUE,
    addr char(64) DEFAULT 'TianJin',
    age int,
    sex char(8)
)
