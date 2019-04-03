CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    username TEXT UNIQUE NOT NULL, 
    password TEXT NOT NULL, 
    salt TEXT NOT NULL);

INSERT INTO users (username, password, salt)
VALUES ('admin', '$2b$10$WqGGs8/U3RUCytBaZZhWOOJfUGsXkCK80.kdFlSD7gsP9ZMABdy9.', 'gh4p10$UY50TJeq08DwT6pFZEb9.eFh4h5hITOCYMy196VBqng5f/8e7mMfK');