-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema CRM System DB
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema CRM System DB
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `CRM System DB` DEFAULT CHARACTER SET utf8 ;
USE `CRM System DB` ;

-- -----------------------------------------------------
-- Table `CRM System DB`.`Utente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Utente` (
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `ruolo` ENUM('cliente', 'operatore', 'manager', 'membro settore sociale') NOT NULL,
  `cf` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`username`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Cliente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Cliente` (
  `cf` VARCHAR(16) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cognome` VARCHAR(45) NOT NULL,
  `dataNascita` DATE NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  `indirizzo` VARCHAR(45) NOT NULL,
  `fax` VARCHAR(45) NULL,
  PRIMARY KEY (`cf`),
  CONSTRAINT `fk_Cliente_1`
    FOREIGN KEY (`cf`)
    REFERENCES `CRM System DB`.`Utente` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Manager`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Manager` (
  `cf` VARCHAR(16) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cognome` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`cf`),
  CONSTRAINT `fk_Manager_1`
    FOREIGN KEY (`cf`)
    REFERENCES `CRM System DB`.`Utente` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Operatore`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Operatore` (
  `cf` VARCHAR(16) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cognome` VARCHAR(45) NOT NULL,
  `manager` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`cf`),
  INDEX `fk_Operatore_1_idx` (`manager` ASC),
  CONSTRAINT `fk_Operatore_1`
    FOREIGN KEY (`manager`)
    REFERENCES `CRM System DB`.`Manager` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Operatore_2`
    FOREIGN KEY (`cf`)
    REFERENCES `CRM System DB`.`Utente` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Gestione`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Gestione` (
  `operatore` VARCHAR(16) NOT NULL,
  `cliente` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`operatore`, `cliente`),
  INDEX `fk_Gestione_1_idx` (`cliente` ASC),
  CONSTRAINT `fk_Gestione_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Gestione_2`
    FOREIGN KEY (`operatore`)
    REFERENCES `CRM System DB`.`Operatore` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`MembroSettoreCommerciale`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`MembroSettoreCommerciale` (
  `cf` VARCHAR(16) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cognome` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`cf`),
  CONSTRAINT `fk_MembroSettoreCommerciale_1`
    FOREIGN KEY (`cf`)
    REFERENCES `CRM System DB`.`Utente` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Inserimento`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Inserimento` (
  `membroSettoreCommerciale` VARCHAR(16) NOT NULL,
  `cliente` VARCHAR(16) NOT NULL,
  `dataInserimento` DATE NULL,
  PRIMARY KEY (`cliente`),
  INDEX `fk_Inserimento_2_idx` (`membroSettoreCommerciale` ASC),
  CONSTRAINT `fk_Inserimento_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Inserimento_2`
    FOREIGN KEY (`membroSettoreCommerciale`)
    REFERENCES `CRM System DB`.`MembroSettoreCommerciale` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`ClienteSocieta`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`ClienteSocieta` (
  `cliente` VARCHAR(16) NOT NULL,
  `nomeSocieta` VARCHAR(45) NOT NULL,
  `partitaIVA` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`cliente`),
  CONSTRAINT `fk_ClienteSocieta_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Telefono`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Telefono` (
  `numero` INT NOT NULL,
  `cliente` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`numero`, `cliente`),
  INDEX `fk_Telefono_1_idx` (`cliente` ASC),
  CONSTRAINT `fk_Telefono_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`PropostaCommerciale`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`PropostaCommerciale` (
  `codiceAlfanumerico` VARCHAR(45) NOT NULL,
  `descrizione` VARCHAR(100) NULL,
  `manager` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`codiceAlfanumerico`),
  INDEX `fk_PropostaCommerciale_1_idx` (`manager` ASC),
  CONSTRAINT `fk_PropostaCommerciale_1`
    FOREIGN KEY (`manager`)
    REFERENCES `CRM System DB`.`Manager` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Accettazione`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Accettazione` (
  `cliente` VARCHAR(16) NOT NULL,
  `propostaCommerciale` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`cliente`, `propostaCommerciale`),
  INDEX `fk_Accettazione_2_idx` (`propostaCommerciale` ASC),
  CONSTRAINT `fk_Accettazione_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Accettazione_2`
    FOREIGN KEY (`propostaCommerciale`)
    REFERENCES `CRM System DB`.`PropostaCommerciale` (`codiceAlfanumerico`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Sede`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Sede` (
  `indirizzo` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`indirizzo`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`SalaRiunione`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`SalaRiunione` (
  `numeroSala` INT NOT NULL,
  `sede` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`numeroSala`, `sede`),
  INDEX `fk_SalaRiunione_1_idx` (`sede` ASC),
  INDEX `index3` (`numeroSala` ASC),
  CONSTRAINT `fk_SalaRiunione_1`
    FOREIGN KEY (`sede`)
    REFERENCES `CRM System DB`.`Sede` (`indirizzo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Conversazione`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Conversazione` (
  `cliente` VARCHAR(16) NOT NULL,
  `operatore` VARCHAR(16) NOT NULL,
  `notaTestuale` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`cliente`, `operatore`, `notaTestuale`),
  INDEX `fk_Conversazione_2_idx` (`operatore` ASC),
  INDEX `fk_Conversazione_1_idx` (`cliente` ASC),
  INDEX `nota` (`notaTestuale` ASC),
  CONSTRAINT `fk_Conversazione_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Conversazione_2`
    FOREIGN KEY (`operatore`)
    REFERENCES `CRM System DB`.`Operatore` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Riferimento`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Riferimento` (
  `cliente` VARCHAR(16) NOT NULL,
  `operatore` VARCHAR(16) NOT NULL,
  `notaTestuale` VARCHAR(100) NOT NULL,
  `propostaCommerciale` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`cliente`, `operatore`, `notaTestuale`, `propostaCommerciale`),
  INDEX `fk_Riferimento_2_idx` (`operatore` ASC),
  INDEX `fk_Riferimento_3_idx` (`notaTestuale` ASC),
  INDEX `fk_Riferimento_4_idx` (`propostaCommerciale` ASC),
  CONSTRAINT `fk_Riferimento_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Riferimento_2`
    FOREIGN KEY (`operatore`)
    REFERENCES `CRM System DB`.`Operatore` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Riferimento_3`
    FOREIGN KEY (`notaTestuale`)
    REFERENCES `CRM System DB`.`Conversazione` (`notaTestuale`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Riferimento_4`
    FOREIGN KEY (`propostaCommerciale`)
    REFERENCES `CRM System DB`.`PropostaCommerciale` (`codiceAlfanumerico`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`PropostaCommercialeTerminata`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`PropostaCommercialeTerminata` (
  `propostaCommerciale` VARCHAR(45) NOT NULL,
  `dataTerminazione` DATE NOT NULL,
  `manager` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`propostaCommerciale`),
  INDEX `fk_PropostaCommercialeTerminata_2_idx` (`manager` ASC),
  CONSTRAINT `fk_PropostaCommercialeTerminata_1`
    FOREIGN KEY (`propostaCommerciale`)
    REFERENCES `CRM System DB`.`PropostaCommerciale` (`codiceAlfanumerico`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_PropostaCommercialeTerminata_2`
    FOREIGN KEY (`manager`)
    REFERENCES `CRM System DB`.`Manager` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM System DB`.`Appuntamento`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CRM System DB`.`Appuntamento` (
  `sala` INT NOT NULL,
  `sede` VARCHAR(45) NOT NULL,
  `data` DATE NOT NULL,
  `ora` TIME NOT NULL,
  `cliente` VARCHAR(16) NOT NULL,
  `operatore` VARCHAR(16) NOT NULL,
  `propostaCommerciale` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`sala`, `sede`, `data`, `ora`),
  INDEX `fk_Appuntamento_1_idx` (`cliente` ASC),
  INDEX `fk_Appuntamento_2_idx` (`operatore` ASC),
  INDEX `fk_Appuntamento_3_idx` (`sede` ASC),
  INDEX `fk_Appuntamento_5_idx` (`propostaCommerciale` ASC),
  CONSTRAINT `fk_Appuntamento_1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM System DB`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Appuntamento_2`
    FOREIGN KEY (`operatore`)
    REFERENCES `CRM System DB`.`Operatore` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Appuntamento_3`
    FOREIGN KEY (`sede`)
    REFERENCES `CRM System DB`.`Sede` (`indirizzo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Appuntamento_4`
    FOREIGN KEY (`sala`)
    REFERENCES `CRM System DB`.`SalaRiunione` (`numeroSala`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Appuntamento_5`
    FOREIGN KEY (`propostaCommerciale`)
    REFERENCES `CRM System DB`.`PropostaCommerciale` (`codiceAlfanumerico`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `CRM System DB` ;

-- -----------------------------------------------------
-- procedure visualizza_cliente
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `visualizza_cliente` (in codice_fiscale_cliente VARCHAR(16))
BEGIN
	declare var_nome_societa int;
    declare var_partitaIVA int;
    set transaction read only;
    set transaction isolation level read committed;
		#fare select di cf, nome, cognome,(se è società anche nome società e IVA),
        #	data nascita, email, telefoni, fax, indirizzo, proposte accettate del join con `cf`= codice_fiscale_cliente 
        #select ``, `nome` as 'corso di laurea' from `esami` join `corsi_laurea` on `corso_laurea` = `codice` where `docente` = var_docente;
		select `nomeSocieta`, `partitaIVA` 
        from `ClienteSocieta` left join `Cliente` on `cliente` = `cf`
        into var_nome_societa, var_partitaIVA;
        
        if var_nome_societa = NULL then
			select `Cliente`, `numero`, `descrizione` #anche nota testuale
            from `Cliente` join `Telefono` on `cf` = `Telefono`.`cliente` 
				join `Accettazione` on `cf` = `Accettazione`.`cliente`
			where `cf` = codice_fiscale_cliente;
		end if;
        
        
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_elenco_clienti
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `visualizza_elenco_clienti` ( in codice_fiscale_operatore VARCHAR(16))
BEGIN
	set transaction read only;
    set transaction isolation level read committed;
		
        select `cf`, `nome`, `cognome` 
		from `Gestione` join `Cliete` on `cliente` = `cf` 
        where `operatore` = codice_fiscale_operatore;
        
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_appuntamento
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `inserisci_appuntamento` ( in numero_sala int, in indirizzo_sede VARCHAR(45), in data_appuntamento date, in ora_appuntamento time, in codice_fiscale_cliente VARCHAR(16), in codice_fiscale_operatore VARCHAR(16), in codice_proposta VARCHAR(45))
BEGIN
	insert into `Appuntamento`(`sala`, `sede`, `data`, `ora`, `cliente`, `operatore`, `propostaCommericiale`) values ( numero_sala, indirizzo_sede, data_appuntamento, ora_appuntamento, codice_fiscale_cliente, codice_fiscale_operatore, codice_proposta);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_appuntamenti
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `visualizza_appuntamenti` ( in codice_fiscale_operatore VARCHAR(16))
BEGIN
	set transaction read only;
    set transaction isolation level read committed;

        select `C`.`cf`, `C`.`nome`, `C`.`cognome`, `data`, `ora`, `sede`, `sala`
		from `Appuntamento` join `Cliente` as `C` on `cliente` = `C`.`cf` 
		where `operatore` = codice_fiscale_operatore;
        
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_proposta
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `inserisci_proposta` (in codice VARCHAR(45), in descrizione VARCHAR(100), in codice_fiscale_manager VARCHAR(16))
BEGIN
	insert into `PropostaCommerciale` values (codice, descrizione, codice_fiscale_manager);
	
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure archivia_proposta
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `archivia_proposta` (in codice_proposta_terminata VARCHAR(45), in codice_fiscale_manager VARCHAR(16))
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level read committed;
    start transaction;
    
		delete from `PropostaCommerciale` where `codice` = codice_proposta_terminata;
		insert into `PropostaCommercialeTerminata` values ( codice_proposta_commerciale, curdate(), codice_fiscale_manager);
        
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_cliente
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `inserisci_cliente` (in codice_fiscale VARCHAR(16), in nome VARCHAR(45), in cognome VARCHAR(45), in email VARCHAR(45), in indirizzo VARCHAR(45), in fax VARCHAR(45), in data_nascita date, in codice_fiscale_manager VARCHAR(16))
BEGIN
	declare var_num_cliente int;
    set transaction isolation level read committed;
    start transaction;
		
        
        select count(*) 
		from `Inserimento` 
        where `cliente` = codice_fiscale
        into var_num_cliente;
        
		if var_num_cliente > 0 then
			signal sqlstate '45001' set message_text = "The client is already registered in the CRM system";
		end if;
    
		insert into `Cliente` (`cf`, `nome`, `cognome`, `dataNascita`, `email`, `indirizzo`, `fax`) values (codice_fiscale, nome, cognome, data_nascita, email, indirizzo, fax);
		insert into `Inserimento` values ( codice_fiscale_manager, codice_fiscale, curdate());
		#imposto come username il codice fiscale --> potrei farlo cambiare all'utente insieme all password
		
        insert into `Utente` values ( codice_fiscale, CRYPT_GEN_RANDOM(8), 'cliente', codice_fiscale);
        
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_operatore
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `inserisci_operatore` (in codice_fiscale VARCHAR(16), in nome VARCHAR(45), in cognome VARCHAR(45), in codice_fiscale_manager VARCHAR(16))
BEGIN
	insert into `Operatore` (`cf`, `nome`, `cognome`, `manager`) values (codice_fiscale, nome, cognome, codice_fiscale_manager);
    
    insert into `Utente` values ( codice_fiscale, CRYPT_GEN_RANDOM(8), 'operatore', codice_fiscale);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_conversazione
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `inserisci_conversazione` (in codice_fiscale_cliente VARCHAR(16), in codice_fiscale_operatore VARCHAR(16), in nota_testuale VARCHAR(100))
BEGIN
	insert into `Conversazione` (`cliente`, `operatore`, `notaTestuale`) values (codice_fiscale_cliente, codice_fiscale_operatore, nota_testuale);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modifica_nota_conversazione
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `modifica_nota_conversazione` ()
BEGIN

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure elimina_nota_conversazione
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `elimina_nota_conversazione` ()
BEGIN

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_proposta_accettata
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `inserisci_proposta_accettata` ( in codice_fiscale_cliente VARCHAR(16), in codice_proposta VARCHAR(45))
BEGIN
	insert into `Accettazione` (`cliente`, `propostaCommerciale`) values ( codice_fiscale_cliente, codice_proposta);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure login
-- -----------------------------------------------------

DELIMITER $$
USE `CRM System DB`$$
CREATE PROCEDURE `login` (in username VARCHAR(16), in pass VARCHAR(45), out role int, out codice_fiscale VARCHAR(16))
BEGIN
	declare var_user ENUM('cliente', 'operatore', 'manager', 'membro settore commerciale');
    
	select `ruolo`, `cf` from `Utente`
		where `username` = username
        and `password` = md5(pass)
        into var_user, codice_fiscale;
        
	if var_user = 'cliente' then
		set role = 1;
	elseif var_user = 'operatore' then
		set role = 2;
	elseif var_user = 'manager' then
		set role = 3;
	elseif var_user = 'membro settore commerciale' then
		set role = 4;
	else
		set role = 5;
	end if;
    
END$$

DELIMITER ;
CREATE USER 'cliente'@'localhost' IDENTIFIED BY 'cliente';

GRANT EXECUTE ON procedure `CRM System DB`.`visualizza_cliente` TO 'cliente'@'localhost';
CREATE USER 'operatore'@'localhost' IDENTIFIED BY 'operatore';

GRANT EXECUTE ON procedure `CRM System DB`.`elimina_nota_conversazione` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`inserisci_appuntamento` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`inserisci_conversazione` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`inserisci_proposta_accettata` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`modifica_nota_conversazione` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`visualizza_appuntamenti` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`visualizza_cliente` TO 'operatore'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`visualizza_elenco_clienti` TO 'operatore'@'localhost';
CREATE USER 'manager'@'localhost' IDENTIFIED BY 'manager';

GRANT EXECUTE ON procedure `CRM System DB`.`archivia_proposta` TO 'manager'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`inserisci_operatore` TO 'manager'@'localhost';
GRANT EXECUTE ON procedure `CRM System DB`.`inserisci_proposta` TO 'manager'@'localhost';
CREATE USER 'membro settore sociale'@'localhost' IDENTIFIED BY 'membro settore sociale';

GRANT EXECUTE ON procedure `CRM System DB`.`inserisci_cliente` TO 'membro settore sociale'@'localhost';
CREATE USER 'login'@'localhost' IDENTIFIED BY 'login';

GRANT EXECUTE ON procedure `CRM System DB`.`login` TO 'login'@'localhost';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
