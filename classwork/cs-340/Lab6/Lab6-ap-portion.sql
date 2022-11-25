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
       SUM(invoice_total) AS invoice_total_sum FROM vendors
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

SELECT COUNT(orders.orderid) as order_count,
       SUM(taxamount) as tax_total
FROM orders;

SELECT c.categoryname,
       MAX(p.listprice) AS most_expensive_product
FROM categories c, products p
WHERE c.categoryid == p.categoryid
GROUP BY c.categoryname
ORDER BY p.listprice DESC;

SELECT emailaddress,
       SUM(itemprice) as item_price_total,
       SUM(discountamount) as discountamounttotal
FROM orders
JOIN customers c on orders.customerid = c.customerid
JOIN orderitems o on orders.orderid = o.orderid
GROUP BY emailaddress
ORDER BY item_price_total DESC;

SELECT emailaddress,
       COUNT(emailaddress) AS order_count,
       SUM(itemprice) as order_total
FROM customers, orderitems
JOIN orders o on customerid = o.customerid
GROUP BY emailaddress
HAVING COUNT(emailaddress) > 1
ORDER BY order_count DESC;


