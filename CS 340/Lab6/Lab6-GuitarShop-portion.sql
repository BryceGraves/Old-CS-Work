SELECT COUNT(orders.orderid) as order_count,
       SUM(taxamount) as tax_total
FROM orders;

SELECT c.categoryname,
       MAX(p.listprice)
FROM categories c, products p
WHERE c.categoryid == p.categoryid
GROUP BY c.categoryname
ORDER BY p.listprice DESC;
