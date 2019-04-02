SELECT * FROM invoices;

INSERT INTO terms
VALUES (6, 'Net due 120 days', 120);

UPDATE terms
SET terms_description = 'Net due 125 days', terms_due_days = 125
WHERE terms_id == 6;

DELETE FROM terms
WHERE terms_id == 6;

INSERT INTO invoices (vendor_id,
  invoice_number,
  invoice_date,
  invoice_total,
  payment_total,
  credit_total,
  terms_id,
  invoice_due_date,
  payment_date)
VALUES (32,
  'AX-014-027',
  '2014-08-01',
  434.58,
  0.00,
  0.00,
  2,
  '2014-08-31',
  null);

INSERT INTO invoice_line_items
  (invoice_id,invoice_sequence,
   account_number,
   line_item_amount,
   line_item_description)
VALUES
       ((SELECT last_insert_rowid()),
          1,
          160,
          180.23,
          'Hard drive'),
       ((SELECT last_insert_rowid()),
          2,
          527,
          254.35,
          'Exchange Server update');

UPDATE invoices
SET credit_total = (invoice_total * 0.1),
    payment_total = invoice_total - credit_total
WHERE invoice_id = 115;

UPDATE vendors
SET default_account_number = 403
WHERE vendor_id = 44;

DELETE FROM invoices_line_items
WHERE invoice_id = 115;

DELETE FROM invoices
WHERE invoice_id = 115;
