drop table if exists Categories;
drop table if exists Products;
drop table if exists Customers;
drop table if exists Addresses;
drop table if exists Orders;
drop table if exists OrderItems;
drop table if exists Administrators;

vacuum;

create table categories (
  categoryid        int            primary key   ,
  categoryname      varchar(255)   not null      unique
);

create table products (
  productid         int            primary key   ,
  categoryid        int            references categories (categoryid), 
  productcode       varchar(10)    not null      unique,
  productname       varchar(255)   not null,
  description       text           not null,
  listprice         money          not null,
  discountpercent   money          not null      default 0.00,
  dateadded         datetime                     default null
);

create table customers (
  customerid           int            primary key   ,
  emailaddress         varchar(255)   not null      unique,
  password             varchar(60)    not null,
  firstname            varchar(60)    not null,
  lastname             varchar(60)    not null,
  shippingaddressid    int                          default null,
  billingaddressid     int                          default null
);

create table addresses (
  addressid          int            primary key   ,
  customerid         int            references customers (customerid),
  line1              varchar(60)    not null,
  line2              varchar(60)                  default null,
  city               varchar(40)    not null,
  state              varchar(2)     not null,
  zipcode            varchar(10)    not null,
  phone              varchar(12)    not null,
  disabled           int            not null      default 0
);

create table orders (
  orderid           int            primary key  ,
  customerid        int            references customers (customerid),
  orderdate         datetime       not null,
  shipamount        money          not null,
  taxamount         money          not null,
  shipdate          datetime                    default null,
  shipaddressid     int            not null,
  cardtype          varchar(50)    not null,
  cardnumber        char(16)       not null,
  cardexpires       char(7)        not null,
  billingaddressid  int            not null    
);

create table orderitems (
  itemid             int            primary key  ,
  orderid            int            references orders (orderid),
  productid          int            references products (productid),
  itemprice          money  not null,
  discountamount     money  not null,
  quantity           int            not null    
);

create table administrators (
  adminid           int            primary key   ,
  emailaddress      varchar(255)   not null,
  password          varchar(255)   not null,
  firstname         varchar(255)   not null,
  lastname          varchar(255)   not null
);
