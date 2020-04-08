set sql_safe_updates = 0;
use library;
drop database library;
select BookID, Title, BorrowDate, RetDate from record natural join book where CardID = 123;
select * from record;
select * from book;
delete from record where AdminID = 'cxy2';
delete from record where BookID = 122;
delete from book where BookID = 122;
delete from book where BookID = 4567;
delete from admin where AdminID = 'cxy1';
insert into record value ('123', '12121', '2000-01-01', '2000-01-03', 'root');
select * from card where CardID = '456';
delete from card where CardID = '456';

select * from book where Total != Stock;
