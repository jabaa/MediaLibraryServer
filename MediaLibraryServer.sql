DROP TABLE users;
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    username TEXT UNIQUE NOT NULL, 
    password TEXT NOT NULL, 
    salt TEXT NOT NULL);

INSERT INTO users (id, username, password, salt)
VALUES (0, 'admin', '$2b$10$WqGGs8/U3RUCytBaZZhWOOJfUGsXkCK80.kdFlSD7gsP9ZMABdy9.', 'gh4p10$UY50TJeq08DwT6pFZEb9.eFh4h5hITOCYMy196VBqng5f/8e7mMfK');

DROP TABLE roles;
CREATE TABLE roles (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    role TEXT UNIQUE NOT NULL);

INSERT INTO roles (id, role)
VALUES (0, 'admin'), (1, 'user');

DROP TABLE users_roles;
CREATE TABLE users_roles (
    user INTEGER NOT NULL,
    role INTEGER NOT NULL);

INSERT INTO users_roles (user, role)
VALUES (0, 0), (0, 1);