-- MySQL Workbench Forward Engineering

-- -----------------------------------------------------
-- Schema oamkR5ATM
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema oamkR5ATM
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `oamkR5ATM` DEFAULT CHARACTER SET utf8 ;
USE `oamkR5ATM` ;

-- -----------------------------------------------------
-- Table `oamkR5ATM`.`customer`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `oamkR5ATM`.`customer` (
  `idCustomer` INT NOT NULL AUTO_INCREMENT,
  `firstname` VARCHAR(45) NULL,
  `lastname` VARCHAR(45) NULL,
  `phone` VARCHAR(45) NULL,
  PRIMARY KEY (`idCustomer`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `oamkR5ATM`.`accounts`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `oamkR5ATM`.`accounts` (
  `idaccounts` INT NOT NULL AUTO_INCREMENT,
  `type` ENUM('debit', 'credit') NOT NULL,
  `balance` DOUBLE NULL,
  `creditlimit` DOUBLE NULL,
  `idcustomer` INT NULL,
  PRIMARY KEY (`idaccounts`),
  INDEX `idcustomer_idx` (`idcustomer` ASC) VISIBLE,
  CONSTRAINT `idcustomer`
    FOREIGN KEY (`idcustomer`)
    REFERENCES `oamkR5ATM`.`customer` (`idCustomer`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `oamkR5ATM`.`card`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `oamkR5ATM`.`card` (
  `idcard` INT NOT NULL AUTO_INCREMENT,
  `type` ENUM('debit', 'credit', 'dual') NOT NULL,
  `cardpin` VARCHAR(255) NULL,
  PRIMARY KEY (`idcard`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `oamkR5ATM`.`transaction`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `oamkR5ATM`.`transaction` (
  `idtransaction` INT NOT NULL AUTO_INCREMENT,
  `action` VARCHAR(45) NULL,
  `actiontimestamp` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `amount` DOUBLE NULL,
  `idaccounts` INT NOT NULL,
  PRIMARY KEY (`idtransaction`),
  INDEX `idaccount_idx` (`idaccounts` ASC) VISIBLE,
  CONSTRAINT `idaccounts`
    FOREIGN KEY (`idaccounts`)
    REFERENCES `oamkR5ATM`.`accounts` (`idaccounts`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `oamkR5ATM`.`accounts_cards`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `oamkR5ATM`.`accounts_cards` (
  `idaccounts` INT NOT NULL,
  `idcard` INT NOT NULL,
  PRIMARY KEY (`idaccounts`, `idcard`),
  INDEX `idaccounts` (`idaccounts` ASC) VISIBLE,
  INDEX `idcard` (`idcard` ASC) VISIBLE,
  CONSTRAINT `fk_accounts_id`
    FOREIGN KEY (`idaccounts`)
    REFERENCES `oamkR5ATM`.`accounts` (`idaccounts`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_cards_id`
    FOREIGN KEY (`idcard`)
    REFERENCES `oamkR5ATM`.`card` (`idcard`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
