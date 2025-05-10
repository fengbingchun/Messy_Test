CREATE DATABASE glpk;
CREATE USER glpk@localhost IDENTIFIED BY 'gnu';
GRANT ALL PRIVILEGES ON glpk.* TO glpk@localhost;
USE glpk;
# production capacity
DROP TABLE transp_capa;
CREATE TABLE transp_capa (
  PLANT TEXT(127),
  CAPA  REAL,
  PRIMARY KEY ( PLANT(127) )
  );
INSERT INTO transp_capa ( PLANT, CAPA ) VALUES ( 'Seattle',   350 );
INSERT INTO transp_capa ( PLANT, CAPA ) VALUES ( 'San Diego', 600 );
# demand
DROP TABLE transp_demand;
CREATE TABLE transp_demand (
  MARKET TEXT(127),
  DEMAND REAL,
  PRIMARY KEY ( MARKET(127) )
  );
INSERT INTO transp_demand ( MARKET, DEMAND ) VALUES ( 'New York', 325 );
INSERT INTO transp_demand ( MARKET, DEMAND ) VALUES ( 'Chicago', 300 );
INSERT INTO transp_demand ( MARKET, DEMAND ) VALUES ( 'Topeka', 275 );
# distance
DROP TABLE transp_dist;
CREATE TABLE transp_dist (
  LOC1 TEXT(127),
  LOC2 TEXT(127),
  DIST REAL,
  PRIMARY KEY ( LOC1(127), LOC2(127) )
  );
INSERT INTO transp_dist ( LOC1, LOC2, DIST ) VALUES ( 'Seattle',   'New York', 2.5 );
INSERT INTO transp_dist ( LOC1, LOC2, DIST ) VALUES ( 'Seattle',   'Chicago', 1.7 );
INSERT INTO transp_dist ( LOC1, LOC2, DIST ) VALUES ( 'Seattle',   'Topeka', 1.8 );
INSERT INTO transp_dist ( LOC1, LOC2, DIST ) VALUES ( 'San Diego', 'New York', 2.5 );
INSERT INTO transp_dist ( LOC1, LOC2, DIST ) VALUES ( 'San Diego', 'Chicago', 1.8 );
INSERT INTO transp_dist ( LOC1, LOC2, DIST ) VALUES ( 'San Diego', 'Topeka', 1.4 );
# result
DROP TABLE transp_result;
CREATE TABLE transp_result (
  LOC1     TEXT(127),
  LOC2     TEXT(127),
  QUANTITY REAL,
  PRIMARY KEY ( LOC1(127), LOC2(127) )
  );
