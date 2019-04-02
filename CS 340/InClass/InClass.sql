drop table if exists Department;
drop table if exists College;
drop table if exists StudentMajor;
drop table if exists Student;
drop table if exists Person;
drop table if exists ClassFaculty;
drop table if exists Class;
drop table if exists ClassStudents;
drop table if exists Faculty;
drop table if exists Rank;

vacuum;

create table College
(
  CollegeId integer
    constraint College_pk
      primary key,
  CollegeDesc varchar [200] not null,
  CollegeDeanId integer default null
  --, foreign key (CollegeDeanId) REFERENCES Faculty(FacuktyId)
);

create unique index College_CollegeDesc_uindex
  on College (CollegeDesc);

create table Department
(
  DepartmentId INTEGER
    constraint Department_pk
      primary key,
  DepartmentDesc varchar(200),
  CollegeId integer
    references College
      on update cascade on delete cascade
);

create table Class
(
  ClassId INTEGER
    constraint Class_pk
      primary key,
  ClassDesc varchar[200],
  DepartmentId INTEGER
    references Department
      on delete cascade,
  Credits integer,
  ClassName varchar[200]
);

create unique index Class_ClassName_uindex
  on Class (ClassName);

create table Person
(
  PersonId integer
    constraint Person_pk
      primary key,
  FName varchar(200),
  MName varchar(200),
  LName varchar(200),
  PhoneNumber varchar(200),
  PhoneMobile varchar(200),
  BirthDate date,
  EMail varchar(200)
);

create table Rank
(
  RankId integer
    constraint Rank_pk
      primary key,
  RankDesc varchar(200)
);

create table Faculty
(
  FacultyId integer
    constraint Faculty_pk
      primary key
    references Person
      on update cascade on delete cascade,
  SupervisorId integer,
  Salary float,
  RankId integer
    references Rank
      on update cascade on delete cascade,
  HireDate date,
  DepartmentId integer
    references Department
      on update cascade on delete cascade,
  PhoneCampus varchar(200)
);

create table ClassFaculty
(
  FacultyId integer
    references Faculty
      on update cascade on delete cascade,
  ClassId integer
    references Class
      on update cascade on delete cascade,
  constraint ClassFaculty_pk
    primary key (FacultyId, ClassId)
);

create table Student
(
  StudentId integer
    constraint Student_pk
      primary key
    references Person
      on update cascade on delete cascade,
  BeginDate date,
  CurrentStudent integer
);

create table ClassStudents
(
  StudentId integer
    references Student
      on delete cascade,
  ClassId integer
    references Class
      on delete cascade,
  ClassTerm varchar [200],
  StudentGrade varchar[10],
  constraint ClassStudents_pk
    primary key (StudentId, ClassId)
);

create table StudentMajor
(
  StudentId integer
    references Student
      on update cascade on delete cascade,
  AdvisorId INTEGER
    references Faculty
      on update set null on delete set null,
  DepartmentId INTEGER
    references Department
      on delete cascade,
  GraduationDate date,
  constraint StudentMajor_pk
    primary key (StudentId, AdvisorId)
);

create table StudentStatus
(
  StatusId integer
    constraint StudentStatus_pk
      primary key,
  StatusDesc varchar(200)
);