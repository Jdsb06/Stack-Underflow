CREATE DATABASE StackUnderflow; --command 1

USE StackUnderflow;   --command 2

create table Master                                --command 3
(
    item_id     int auto_increment
        primary key,
    name        varchar(50)  null,
    category    varchar(50)  null,
    description varchar(150) null
);

create table Customer_Order                        --command 4
(
    cust_order_id   int auto_increment
        primary key,
    item_id         int         null,
    quantity        int         null,
    status          varchar(20) null,
    order_date      datetime    null,
    completed_order datetime    null,
    constraint Customer_Order_Master_item_id_fk
        foreign key (item_id) references Master (item_id)
);

create table Purchase_Manufacture                  --command 5
(
    purchase_id     int auto_increment
        primary key,
    item_id         int         null,
    quantity        int         null,
    status          varchar(20) null,
    order_date      datetime    null,
    completed_order datetime    null,
    constraint Purchase_Manufacture_Master_item_id_fk
        foreign key (item_id) references Master (item_id)
);

create table Transaction                            --command 6
(
    tran_id   int auto_increment
        primary key,
    item_id   int         null,
    type      varchar(20) null,
    quantity  int         null,
    tran_date datetime    null,
    constraint Transaction_Master_item_id_fk
        foreign key (item_id) references Master (item_id)
);

create table User                                    --command 7
(
    user_id   int auto_increment
        primary key,
    user_name varchar(50) not null,
    password  varchar(50) null,
    constraint User_pk_2
        unique (user_name)
);
