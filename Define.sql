use Exp03_DB;
set FOREIGN_KEY_CHECKS = 0;
drop table if exists book,
card,
borrow;
set FOREIGN_KEY_CHECKS = 1;
create table book (
    bno char(8),
    category char(10),
    title varchar(40),
    press varchar(30),
    year int,
    author varchar(20),
    price decimal(7 , 2 ),
    total int,
    stock int,
    primary key (bno)
)  character set=utf8;
create table card (
    cno char(7),
    name varchar(20),
    department varchar(40),
    type char(1),
    primary key (cno),
    constraint check_type check (type in ('T' , 'G', 'U', 'O'))
)  character set=utf8;
create table borrow (
    cno char(7),
    bno char(8),
    borrow_date date,
    return_date date,
    foreign key (bno)
        references book (bno)
        on delete cascade,
    foreign key (cno)
        references card (cno)
        on update cascade
)  character set=utf8;

insert into book value("03580765", "Poem", "Walker Prairie", "Square", 322, "Anthony Hanson", 22.0, 99, 22);
insert into card value("123", "cxy", );