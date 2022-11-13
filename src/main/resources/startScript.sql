drop database if exists `bonus_system`;
create database `bonus_system`;

use `bonus_system`;

drop table if exists `user_role`;
drop table if exists `employee_task`;
drop table if exists `user`;
drop table if exists `employee`;
drop table if exists `task`;
drop table if exists `role`;
drop table if exists `bonus`;

create table `bonus`
(
    id     int         not null
        primary key,
    type   varchar(20) not null,
    amount float       not null
);

create table `employee`
(
    id         int auto_increment
        primary key,
    first_name varchar(20) not null,
    last_name  varchar(20) not null
);

create table `role`
(
    id   int         not null
        primary key,
    name varchar(20) not null
);

create table `task`
(
    id            int auto_increment
        primary key,
    description   text                                not null,
    creation_time timestamp default CURRENT_TIMESTAMP not null,
    bonus_id      int                                 not null,
    constraint task_bonus_id_fk
        foreign key (bonus_id) references bonus (id)
);

create table `employee_task`
(
    id          int auto_increment
        primary key,
    employee_id int                       not null,
    task_id     int                       not null,
    status      varchar(20) default 'new' not null,
    constraint employee_task_employee_id_fk
        foreign key (employee_id) references employee (id)
            on delete cascade,
    constraint employee_task_task_id_fk
        foreign key (task_id) references task (id)
            on delete cascade
);

create table `user`
(
    login         varchar(40) not null
        primary key,
    employee_id   int         null,
    password_hash blob        not null,
    constraint user_employee_null_fk
        foreign key (employee_id) references employee (id)
);

create table `user_role`
(
    id         int auto_increment
        primary key,
    user_login varchar(40) not null,
    role_id    int         not null,
    constraint user_role_role_id_fk
        foreign key (role_id) references role (id)
            on delete cascade,
    constraint user_role_user_login_fk
        foreign key (user_login) references user (login)
            on delete cascade
);

