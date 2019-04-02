drop table if exists departments;
drop table if exists employees;
drop table if exists projects;
drop table if exists customers;
drop table if exists departments;
drop table if exists departments;

vacuum;

create table departments
(
  department_number   integer primary key,
  department_name     varchar(50)   not null
);

insert into departments values 
(1,'Accounting'),
(2,'Payroll'),
(3,'Operations'),
(4,'Personnel'),
(5,'Maintenance');

create table employees
(
  employee_id         integer primary key,
  last_name           varchar(35)       not null,
  first_name          varchar(35)       not null,
  department_number   int               not null,
  manager_id          int default null
);

insert into employees values 
(1,'Smith','Cindy',2,null),
(2,'Jones','Elmer',4,1),
(3,'Simonian','Ralph',2,2),
(4,'Hernandez','Olivia',1,9),
(5,'Aaronsen','Robert',2,4),
(6,'Watson','Denise',6,8),
(7,'Hardy','Thomas',5,2),
(8,'O''Leary','Rhea',4,9),
(9,'Locario','Paulo',6,1);

create table projects
(
  project_number    varchar(5)    not null,
  employee_id       int           not null
);

insert into projects values 
('P1011',8),
('P1011',4),
('P1012',3),
('P1012',1),
('P1012',5),
('P1013',6),
('P1013',9),
('P1014',10);

create table customers
(
  customer_id          integer primary key,
  customer_last_name   varchar(30),
  customer_first_name  varchar(30),
  customer_address     varchar(60),
  customer_city        varchar(15),
  customer_state       varchar(15),
  customer_zip         varchar(10),
  customer_phone       varchar(24)
);

insert into customers values 
(1, 'Anders', 'Maria', '345 Winchell Pl', 'Anderson', 'IN', '46014', '(765) 555-7878'),
(2, 'Trujillo', 'Ana', '1298 E Smathers St', 'Benton', 'AR', '72018', '(501) 555-7733'),
(3, 'Moreno', 'Antonio', '6925 N Parkland Ave', 'Puyallup', 'WA', '98373', '(253) 555-8332'),
(4, 'Hardy', 'Thomas', '83 d''Urberville Ln', 'Casterbridge', 'GA', '31209', '(478) 555-1139'),
(5, 'Berglund', 'Christina', '22717 E 73rd Ave', 'Dubuque', 'IA', '52004', '(319) 555-1139'),
(6, 'Moos', 'Hanna', '1778 N Bovine Ave', 'Peoria', 'IL', '61638', '(309) 555-8755'),
(7, 'Citeaux', 'Fred', '1234 Main St', 'Normal', 'IL', '61761', '(309) 555-1914'),
(8, 'Summer', 'Martin', '1877 Ete Ct', 'Frogtown', 'LA', '70563', '(337) 555-9441'),
(9, 'Lebihan', 'Laurence', '717 E Michigan Ave', 'Chicago', 'IL', '60611', '(312) 555-9441'),
(10, 'Lincoln', 'Elizabeth', '4562 Rt 78 E', 'Vancouver', 'WA', '98684', '(360) 555-2680'),
(11, 'Snyder', 'Howard', '2732 Baker Blvd.', 'Eugene', 'OR', '97403', '(503) 555-7555'),
(12, 'Latimer', 'Yoshi', 'City Center Plaza 516 Main St.', 'Elgin', 'OR', '97827', '(503) 555-6874'),
(13, 'Steel', 'John', '12 Orchestra Terrace', 'Walla Walla', 'WA', '99362', '(509) 555-7969'),
(14, 'Yorres', 'Jaime', '87 Polk St. Suite 5', 'San Francisco', 'CA', '94117', '(415) 555-5938'),
(15, 'Wilson', 'Fran', '89 Chiaroscuro Rd.', 'Portland', 'OR', '97219', '(503) 555-9573'),
(16, 'Phillips', 'Rene', '2743 Bering St.', 'Anchorage', 'AK', '99508', '(907) 555-7584'),
(17, 'Wilson', 'Paula', '2817 Milton Dr.', 'Albuquerque', 'NM', '87110', '(505) 555-5939'),
(18, 'Pavarotti', 'Jose', '187 Suffolk Ln.', 'Boise', 'ID', '83720', '(208) 555-8097'),
(19, 'Braunschweiger', 'Art', 'P.O. Box 555', 'Lander', 'WY', '82520', '(307) 555-4680'),
(20, 'Nixon', 'Liz', '89 Jefferson Way Suite 2', 'Providence', 'RI', '02909', '(401) 555-3612'),
(21, 'Wong', 'Liu', '55 Grizzly Peak Rd.', 'Butte', 'MT', '59801', '(406) 555-5834'),
(22, 'Nagy', 'Helvetius', '722 DaVinci Blvd.', 'Concord', 'MA', '01742', '(351) 555-1219'),
(23, 'Jablonski', 'Karl', '305 - 14th Ave. S. Suite 3B', 'Seattle', 'WA', '98128', '(206) 555-4112'),
(24, 'Chelan', 'Donna', '2299 E Baylor Dr', 'Dallas', 'TX', '75224', '(469) 555-8828');
