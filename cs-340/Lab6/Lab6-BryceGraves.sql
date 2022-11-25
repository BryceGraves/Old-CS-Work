SELECT vendors.vendor_id,
       sum(invoice_total) AS invoice_totals_sum
FROM vendors
  JOIN invoices i ON vendors.vendor_id = i.vendor_id
GROUP BY vendors.vendor_id;

SELECT vendors.vendor_name,
       SUM(payment_total) AS payment_total_sum
FROM vendors, invoices
  JOIN vendors v ON invoices.vendor_id = v.vendor_id
GROUP BY vendors.vendor_name
ORDER BY payment_total_sum DESC;

SELECT vendors.vendor_name,
       COUNT(invoice_total) AS invoice_count,
       SUM(invoice_total) AS invoice_total_sum
FROM vendors
  JOIN invoices i ON vendors.vendor_id = i.vendor_id
GROUP BY vendor_name
ORDER BY invoice_count DESC;

SELECT glg.account_description,
       COUNT(ili.account_number) AS line_item_count,
       SUM(ili.line_item_amount) AS line_item_amount_sum
FROM general_ledger_accounts glg
  JOIN invoice_line_items ili ON glg.account_number = ili.account_number
GROUP BY glg.account_description
HAVING line_item_count > 1
ORDER BY line_item_amount_sum DESC;

SELECT count(*) AS order_count,
       SUM(taxamount) AS tax_total
FROM orders;

SELECT categoryname,
       COUNT(p.productid) AS productcount,
       MAX(listprice) AS most_expensive_product
FROM categories c
  JOIN products p ON c.categoryid = p.categoryid
GROUP BY categoryname
ORDER BY productcount DESC;

SELECT emailaddress,
       SUM(oi.itemprice) * oi.quantity AS item_price_total,
       SUM(oi.discountamount) * oi.quantity AS discountamounttotal
FROM customers c
  JOIN orders o ON c.customerid = o.customerid
  JOIN orderitems oi ON o.orderid = oi.orderid
GROUP BY emailaddress
ORDER BY item_price_total DESC;

SELECT emailaddress,
       COUNT(*) AS order_count,
       SUM((oi.itemprice - oi.discountamount) * quantity) AS order_total
FROM customers c
  JOIN orders o ON c.customerid = o.customerid
  JOIN orderitems oi ON o.orderid = oi.orderid
GROUP BY emailaddress
HAVING order_count > 1
ORDER BY order_total DESC;

SELECT emailaddress,
       COUNT(*) AS order_count,
       SUM((oi.itemprice - oi.discountamount) * quantity) AS order_total
FROM customers JOIN orders o ON customers.customerid = o.customerid
  JOIN orderitems oi ON o.orderid = oi.orderid
WHERE oi.itemprice > 400
GROUP BY emailaddress
HAVING order_count > 1
ORDER BY order_total DESC;

SELECT emailaddress,
       COUNT(DISTINCT productid) AS number_of_products
FROM customers
  JOIN orders o ON customers.customerid = o.customerid
  JOIN orderitems oi ON o.orderid = oi.orderid
GROUP BY emailaddress
HAVING number_of_products > 1;
