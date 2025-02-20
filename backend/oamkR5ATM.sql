-- Drop the database if it exists
DROP DATABASE IF EXISTS `oamkR5ATM`;

-- Create the database
CREATE SCHEMA IF NOT EXISTS `oamkR5ATM` DEFAULT CHARACTER SET utf8;
USE `oamkR5ATM`;

-- Drop tables if they exist
DROP TABLE IF EXISTS `accounts_cards`;
DROP TABLE IF EXISTS `transaction`;
DROP TABLE IF EXISTS `card`;
DROP TABLE IF EXISTS `accounts`;
DROP TABLE IF EXISTS `customer`;

-- Create the customer table
CREATE TABLE `customer` (
  `idCustomer` INT NOT NULL AUTO_INCREMENT,
  `firstname` VARCHAR(45) NULL,
  `lastname` VARCHAR(45) NULL,
  `phone` VARCHAR(45) NULL,
  PRIMARY KEY (`idCustomer`)
) ENGINE = InnoDB;

-- Create the accounts table
CREATE TABLE `accounts` (
  `idaccounts` INT NOT NULL AUTO_INCREMENT,
  `type` ENUM('debit', 'credit') NOT NULL,
  `balance` DOUBLE NULL,
  `creditlimit` DOUBLE NULL,
  `idcustomer` INT NULL,
  PRIMARY KEY (`idaccounts`),
  INDEX `idcustomer_idx` (`idcustomer` ASC),
  CONSTRAINT `fk_idcustomer`
    FOREIGN KEY (`idcustomer`)
    REFERENCES `customer` (`idCustomer`)
    ON DELETE CASCADE
    ON UPDATE CASCADE
) ENGINE = InnoDB;

-- Create the card table
CREATE TABLE `card` (
  `idcard` INT NOT NULL AUTO_INCREMENT,
  `type` ENUM('debit', 'credit', 'dual') NOT NULL,
  `cardpin` VARCHAR(255) NULL,
  `locked` TINYINT(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`idcard`)
) ENGINE = InnoDB;

-- Create the transaction table
CREATE TABLE `transaction` (
  `idtransaction` INT NOT NULL AUTO_INCREMENT,
  `action` VARCHAR(45) NULL,
  `actiontimestamp` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `amount` DOUBLE NULL,
  `idaccounts` INT NOT NULL,
  PRIMARY KEY (`idtransaction`),
  INDEX `idaccount_idx` (`idaccounts` ASC),
  CONSTRAINT `fk_idaccounts`
    FOREIGN KEY (`idaccounts`)
    REFERENCES `accounts` (`idaccounts`)
    ON DELETE CASCADE
    ON UPDATE CASCADE
) ENGINE = InnoDB;

-- Create the accounts_cards table
CREATE TABLE `accounts_cards` (
  `idaccounts` INT NOT NULL,
  `idcard` INT NOT NULL,
  PRIMARY KEY (`idaccounts`, `idcard`),
  INDEX `idaccounts_idx` (`idaccounts` ASC),
  INDEX `idcard_idx` (`idcard` ASC),
  CONSTRAINT `fk_accounts_id`
    FOREIGN KEY (`idaccounts`)
    REFERENCES `accounts` (`idaccounts`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_cards_id`
    FOREIGN KEY (`idcard`)
    REFERENCES `card` (`idcard`)
    ON DELETE CASCADE
    ON UPDATE CASCADE
) ENGINE = InnoDB;
