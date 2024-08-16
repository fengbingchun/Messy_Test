/*
ALTER TABLE：用于在已有的表中添加、删除、修改列
ALTER TABLE table_name ADD column_name data_type -- 添加列
ALTER TABLE table_name DROP COLUMN column_name -- 删除列
*/

ALTER TABLE teacher ADD interest char(64) -- 添加列: interest
ALTER TABLE teacher DROP COLUMN age -- 删除列: age
ALTER TABLE teacher ALTER COLUMN sex int -- 修改列sex类型为int
