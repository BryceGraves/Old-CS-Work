-- If the tables already exist, drop them.
drop table if exists invoice_line_items;
drop table if exists invoices;
drop table if exists vendors;
drop table if exists general_ledger_accounts;
drop table if exists terms;

drop table if exists vendor_contacts;
drop table if exists invoice_archive;


-- recover any space freed up from the table drops.
vacuum;


-- create all the tables
create table if not exists general_ledger_accounts
(
  account_number        int            primary key,
  account_description   varchar(50)    unique
);

create table if not exists terms
(
  terms_id              int            primary key,
  terms_description     varchar(50)    not null,
  terms_due_days        int            not null
);

create table if not exists vendors
(
  vendor_id                     integer        primary key,
  vendor_name                   varchar(50)    not null      unique,
  vendor_address1               varchar(50),
  vendor_address2               varchar(50),
  vendor_city                   varchar(50)    not null,
  vendor_state                  char(2)        not null,
  vendor_zip_code               varchar(20)    not null,
  vendor_phone                  varchar(50),
  vendor_contact_last_name      varchar(50),
  vendor_contact_first_name     varchar(50),
  default_terms_id              int            not null,
  default_account_number        int            not null,
  constraint vendors_fk_terms
    foreign key (default_terms_id)
    references terms (terms_id),
  constraint vendors_fk_accounts
    foreign key (default_account_number)
    references general_ledger_accounts (account_number)
);

create table if not exists invoices
(
  invoice_id            integer        primary key,
  vendor_id             int            not null,
  invoice_number        varchar(50)    not null,
  invoice_date          date           not null,
  invoice_total         decimal(9,2)   not null,
  payment_total         decimal(9,2)   not null      default 0,
  credit_total          decimal(9,2)   not null      default 0,
  terms_id              int            not null,
  invoice_due_date      date           not null,
  payment_date          date,
  constraint invoices_fk_vendors
    foreign key (vendor_id)
    references vendors (vendor_id),
  constraint invoices_fk_terms
    foreign key (terms_id)
    references terms (terms_id)
);

create table if not exists invoice_line_items
(
  invoice_id              integer        not null,
  invoice_sequence        int            not null,
  account_number          int            not null,
  line_item_amount        decimal(9,2)   not null,
  line_item_description   varchar(100)   not null,
  constraint line_items_pk
    primary key (invoice_id, invoice_sequence),
  constraint line_items_fk_invoices
    foreign key (invoice_id)
    references invoices (invoice_id),
  constraint line_items_fk_acounts
    foreign key (account_number)
    references general_ledger_accounts (account_number)
);

-- create the indexes
create index invoices_invoice_date_ix
  on invoices (invoice_date desc);

-- create some test tables that aren't explicitly
-- related to the previous five tables
create table if not exists vendor_contacts
(
  vendor_id       int          primary key,
  last_name       varchar(50)  not null,
  first_name      varchar(50)  not null
);

create table if not exists invoice_archive
(
  invoice_id          int          not null,
  vendor_id           int          not null,
  invoice_number      varchar(50)  not null,
  invoice_date        date         not null,
  invoice_total       decimal(9,2) not null,
  payment_total       decimal(9,2) not null,
  credit_total        decimal(9,2) not null,
  terms_id            int          not null,
  invoice_due_date    date         not null,
  payment_date        date
);
