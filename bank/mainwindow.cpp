#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("W:/project/bank-management-qt-project-main/bank-management-qt-project-main/bank/db/db");
    db.open();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

// All important functions wrote manually.
void MainWindow::getData()
{
    qDebug() << current_user;
    QSqlQuery query;
    query.prepare(" SELECT balance FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            c_balance = query.value("balance").toString();
            c_balance_int = c_balance.toInt();
            qDebug() << "c_balance: "<<c_balance<<"c_balance_int: "<<c_balance_int;
        }
    }
}

void MainWindow::getLastElement()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM user ORDER BY account_no DESC LIMIT 1");
    if(query.exec()){
        while(query.next()){
            l_account_no_int = query.value(0).toInt() + 1;
        }
    }
}

void MainWindow::on_login_forget_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_login_sign_in_button_clicked()
{
    login_email = ui->login_username_or_email_input->text();
    login_password = ui->login_password_input->text();
//    qDebug() << login_email << login_password;
    QSqlQuery query;
    query.exec(" SELECT * FROM user WHERE email = '"+login_email+"' AND password = '"+login_password+"'");
//    qDebug() << query.next();
    if(query.next()){
        ui->stackedWidget->setCurrentIndex(1);
        current_user = login_email;
        acc_no = query.value("account_no").toString();
        dashboard_dataLoad();
    }
    else{
        QMessageBox::warning(this, tr("Sign In"),
                                      tr("Invalid Email or Password. Try again."));
    }
}

void MainWindow::on_login_sign_up_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_fund_tranfer_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);

}

void MainWindow::on_cards_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");

}

void MainWindow::on_forget_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_bill_pay_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_beneficiary_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_services_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}

void MainWindow::on_profile_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);


}

void MainWindow::on_activity_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}
// Pagination for Activity page


void MainWindow::on_dashboard_button_2_clicked()
{
    dashboard_dataLoad();
}


void MainWindow::on_fund_tranfer_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}


void MainWindow::on_profile_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}

//Pagination for Services Page
void MainWindow::on_dashboard_button_4_clicked()
{
    dashboard_dataLoad();
}


void MainWindow::on_fund_tranfer_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);

}


void MainWindow::on_profile_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}

//Pagination for Beneficiary page
void MainWindow::on_dashboard_button_5_clicked()
{
  dashboard_dataLoad();
}


void MainWindow::on_fund_tranfer_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}


void MainWindow::on_profile_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}

//Pagination for bill pay page
void MainWindow::on_dashboard_button_7_clicked()
{
 dashboard_dataLoad();
}


void MainWindow::on_fund_tranfer_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}


void MainWindow::on_profile_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}
// Pagination for Cards page

void MainWindow::on_dashboard_button_8_clicked()
{
    dashboard_dataLoad();

}
void MainWindow::on_fund_tranfer_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}


void MainWindow::on_profile_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

   query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}

// Pagination for fund transfer page
void MainWindow::on_dashboard_button_9_clicked()
{
    dashboard_dataLoad();
}


void MainWindow::on_fund_tranfer_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}


void MainWindow::on_profile_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}

// Pagination for Profile page
void MainWindow::on_dashboard_button_10_clicked()
{
    dashboard_dataLoad();
}


void MainWindow::on_fund_tranfer_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    fund_transfer_dataLoad();
        ui->ft_from_account_no->setText(c_account_no);
        ui->ft_from_available_balance->setText(c_balance);
}


void MainWindow::on_cards_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->cards_american_due_bill->setText("1000.00");
}


void MainWindow::on_bill_pay_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_beneficiary_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_services_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ac_no->setText(acc_no);
}


void MainWindow::on_profile_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQuery query;
    query.prepare(" SELECT * FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            pr_first_name = query.value("first_name").toString();
            pr_last_name = query.value("last_name").toString();
            pr_email = query.value("email").toString();
            pr_dob = query.value("date_of_birth").toString();
            pr_phone = query.value("phone").toString();
            pr_account_no = query.value("account_no").toString();
            pr_city = query.value("city").toString();
            pr_postal_code = query.value("postal_code").toString();
            pr_branch = query.value("branch").toString();
            pr_account_type = query.value("account_type").toString();
        }
    }
    ui->profile_full_name->setText(pr_first_name +" "+ pr_last_name);
    ui->profile_email->setText(pr_email);
    ui->profile_date->setText(pr_dob);
    ui->profile_phone->setText(pr_phone);
    ui->profile_user_name->setText(pr_account_no);
    ui->city->setText(pr_city);
    ui->branch->setText(pr_branch);
    ui->postal_code->setText(pr_postal_code);
    ui->account_type->setText(pr_account_type);

}


void MainWindow::on_activity_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT * FROM 'main'.'transaction' WHERE email = '"+current_user+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());
}


void MainWindow::dashboard_dataLoad()
{

    ui->stackedWidget->setCurrentIndex(1);
    getData();
    getLastElement();
    ui->home_savings->setText(c_balance);
    ui->home_available_balance->setText((c_balance));
    ui->home_ledger->setText(c_balance);

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(db);

    query->prepare("SELECT status,date,amount,time FROM 'main'.'transaction' WHERE email = '"+current_user+"' ORDER BY date DESC LIMIT 10");
    query->exec();
    modal->setQuery(*query);
    ui->tableView_2->setModel(modal);
    if(modal->rowCount() == 0){
        ui->home_transactions_label->setText("No Transaction Yet");
    }
    else{

        ui->home_transactions_label->setText("Last 10 Transactions");
    }


}

void MainWindow::fund_transfer_dataLoad()
{
    QSqlQuery query;
    query.prepare(" SELECT account_no, balance FROM user WHERE email = '"+current_user+"'");
    if(query.exec()){
        while(query.next()){
            c_account_no = query.value("account_no").toString();
            c_balance_int = query.value("balance").toInt();
            ft_to_account = ui->ft_to_account->text();
            ft_to_account_holder = ui->ft_to_ac_holder->text();
            ft_to_narration = ui->ft_to_narration->text();
            transfer_amount = ui->ft_from_transfer_amount->text().toInt();
        }
    }
}


// This function checks if any data in the signup form is missing

// This function is responsive for submit form data into the database.
void MainWindow::on_signup_submit_form_clicked()
{
    signup_account_type = ui->signup_account_type->currentText();
    signup_branch = ui->signup_branch->currentText();
    signup_first_name = ui->signup_first_name->text();
    signup_last_name = ui->signup_last_name->text();
    signup_phone = ui->signup_phone->text();
    signup_email = ui->signup_email->text();
    signup_password = ui->signup_password->text();
    signup_birth_date = ui->signup_birth_date->text();
    signup_address = ui->signup_address->text();
    signup_city = ui->signup_city->text();
    signup_postal_code = ui->signup_postal_code->text();
    signup_country = ui->signup_country->text();
    signup_education = ui->signup_education->currentText();
    getLastElement();
    balance = QString::number(0);
    account_no = QString::number(l_account_no_int);

    if(ui->signup_first_name->text()==NULL ||ui->signup_last_name->text()==NULL || ui->signup_phone->text()==NULL || ui->signup_email->text()==NULL || ui->signup_password->text()==NULL || ui->signup_birth_date->text()==NULL || ui->signup_address->text()==NULL || ui->signup_city->text()==NULL || ui->signup_postal_code->text()==NULL || ui->signup_country->text()==NULL){
        QMessageBox::warning(this, tr("Sign Up"),
                                      tr("Fill up all the required information"));
    }

    else{
        QSqlQuery query;
        query.exec(" SELECT * FROM user WHERE email = '"+signup_email+"'");
        if(!query.next()){
            QSqlQuery query1;
            query1.exec("INSERT INTO user (account_no, first_name, last_name, phone, email, password, date_of_birth, education, city, postal_code, country, address, account_type, branch, balance) "
                        "VALUES ('"+account_no+"', '"+signup_first_name+"', '"+signup_last_name+"', '"+signup_phone+"', '"+signup_email+"', '"+signup_password+"', '"+signup_birth_date+"', '"+signup_education+"', '"+signup_city+"', '"+signup_postal_code+"', '"+signup_country+"', '"+signup_address+"', '"+signup_account_type+"', '"+signup_branch+"', '"+balance+"')");

            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size:20px}");
            msgBox.setText("Account created successfully");
            msgBox.exec();

            ui->signup_first_name->clear();
            ui->signup_last_name->clear();
            ui->signup_phone->clear();
            ui->signup_email->clear();
            ui->signup_password->clear();
            ui->signup_birth_date->clear();
            ui->signup_address->clear();
            ui->signup_city->clear();
            ui->signup_postal_code->clear();
            ui->signup_country->clear();
            ui->stackedWidget->setCurrentIndex(0);

        }
        else{
            QMessageBox::warning(this, tr("Sign Up"),
                                          tr("Email is already in use\nUse another email"));
            ui->signup_email->clear();
        }



    }
}


void MainWindow::on_ft_send_button_clicked()
{
    transfer_amount = ui->ft_from_transfer_amount->text().toInt();
    ft_to_account = ui->ft_to_account->text();
    ft_to_account_holder = ui->ft_to_ac_holder->text();
    ft_to_narration = ui->ft_to_narration->text();

    QSqlQuery query;
    query.exec(" SELECT * FROM user WHERE account_no = '"+ft_to_account+"'");
    if(query.next() && ft_to_account != NULL && ft_to_account_holder != NULL && ft_to_narration != NULL){
        if(c_balance_int >= transfer_amount){
            c_balance_int = c_balance_int - transfer_amount;
            to_balance = query.value("balance").toInt();

            QSqlQuery query;
            query.prepare("UPDATE user SET balance=:balance WHERE email = '"+current_user+"'");
            query.bindValue(":balance", c_balance_int);
            query.exec();
            query.next();

            to_balance = to_balance + transfer_amount;
            query.prepare("UPDATE user SET balance=:ft_balance WHERE account_no = '"+ft_to_account+"'");
            query.bindValue(":ft_balance", to_balance);
            query.exec();
            query.next();


            c_date = QDate::currentDate().toString("dd-MM-yyyy");
            qDebug() << c_date;
            transfer_amount_text = QString::number(transfer_amount);
            qDebug() << transfer_amount_text;
            c_time = QTime::currentTime().toString("hh:mm AP");
            qDebug() << c_time;
            QSqlQuery query1;
            query1.exec("INSERT INTO 'main'.'transaction' (email, status, date, amount, time) "
                        "VALUES ('"+current_user+"', 'Transfer', '"+c_date+"', '"+transfer_amount_text+"', '"+c_time+"')");
            query1.next();

            QMessageBox msgBox;
                msgBox.setStyleSheet("QLabel{min-width: 500px; min-height: 100px; font-size:20px}");
                msgBox.setText("Taka "+transfer_amount_text+ "\n""Successfully transferred\nto the account: " +ft_to_account+"");
                msgBox.exec();
             ui->ft_from_transfer_amount->clear();
             ui->ft_to_ac_holder->clear();
             ui->ft_to_narration->clear();
             ui->ft_to_account->clear();
        }
        else{
            QMessageBox::warning(this, tr("Fund Transfer"),
                                          tr("Insufficient Balance!"));
        }
    }
    else{
        QMessageBox::warning(this, tr("Fund Transfer"),
                                      tr("Please fill all the fields correctly."));
    }



}


void MainWindow::on_home_schedular_button_clicked()
{
    // logout func
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";

}


void MainWindow::on_signup_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msgBox;
        msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size:20px}");
        msgBox.setText("Check book request submitted.");
        msgBox.exec();
}


void MainWindow::on_pushButton_4_clicked()
{
    //deposit button
    depo_ac_no = ui->deposit_account->text();
    depo_amount = ui->deposit_amount->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT account_no, balance FROM user WHERE account_no = '"+depo_ac_no+"'");

    if(query.exec()){
        if(query.next()){
            depo_balance = query.value("balance").toInt();
            if(depo_ac_no != NULL && depo_amount != NULL){
                depo_balance = depo_balance + depo_amount;
                QSqlQuery query;
                query.prepare("UPDATE user SET balance=:balance WHERE account_no = '"+depo_ac_no+"'");
                query.bindValue(":balance", depo_balance);
                query.exec();
                query.next();

                c_date = QDate::currentDate().toString("dd-MM-yyyy");
                depo_amount_text = QString::number(depo_amount);
                c_time = QTime::currentTime().toString("hh:mm AP");

                QSqlQuery query1;
                query1.exec("INSERT INTO 'main'.'transaction' (email, status, date, amount, time) "
                            "VALUES ('"+current_user+"', 'Deposit', '"+c_date+"', '"+depo_amount_text+"', '"+c_time+"')");
                query1.next();
                QMessageBox msgBox;
                    msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size:20px}");
                    msgBox.setText("BDT "+depo_amount_text+ "\n""Successfully deposited");
                    msgBox.exec();

                ui->deposit_account->clear();
                ui->deposit_amount->clear();
                ui->lineEdit_17->clear();
            }
            else{
                QMessageBox::warning(this, tr("Deposit"),
                                              tr("Insert all the required data"));
            }
        }
        else{
            QMessageBox::warning(this, tr("Deposit"),
                                          tr("Wrong Account Number"));
        }
    }

}


void MainWindow::on_dashboard_button_clicked()
{
    dashboard_dataLoad();
}


void MainWindow::on_home_schedular_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}


void MainWindow::on_home_schedular_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}




void MainWindow::on_home_schedular_button_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}


void MainWindow::on_home_schedular_button_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}


void MainWindow::on_home_schedular_button_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}


void MainWindow::on_home_schedular_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}


void MainWindow::on_home_schedular_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->login_username_or_email_input->clear();
    ui->login_password_input->clear();
    current_user = "";
}


void MainWindow::on_forget_submit_button_clicked()
{
       forg_phone = ui->forget_mobile_no_input->text();
       forg_acc = ui->forget_account_no->text();
       forg_email = ui->forget_email_input->text();
       forg_new_pass = ui ->forget_new->text();

       QSqlQuery query;
               query.exec("SELECT password FROM user WHERE email = '"+forg_email+"' AND phone = '"+forg_phone+"' AND account_no = '"+forg_acc+"'");
               if(query.next()){
                   QSqlQuery query1;
                    query1.prepare("UPDATE user SET password=:password WHERE account_no = '"+forg_acc+"'");
                    query1.bindValue(":password", forg_new_pass);
                    query1.exec();
                    query1.next();
                    QMessageBox msgBox;
                        msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size:20px}");
                        msgBox.setText("Password successfully changed.");
                        msgBox.exec();

                    ui->forget_mobile_no_input->clear();
                    ui->forget_account_no->clear();
                    ui->forget_email_input->clear();
                    ui ->forget_new->clear();
                    ui->stackedWidget->setCurrentIndex(0);

               }
               else{
                   QMessageBox::warning(this, tr("Forgot Password"),
                                                 tr("Password reset failed"));
                   ui->forget_mobile_no_input->clear();
                   ui->forget_account_no->clear();
                   ui->forget_email_input->clear();
                   ui ->forget_new->clear();
               }


}


void MainWindow::on_cards_new_cards_order_now_button_clicked()
{
    ui->cards_new_card_choose_type->currentText();
    if(ui->cards_new_card_choose_type->currentText() == "Choose Card Type"){
        QMessageBox::warning(this, tr("Card"),
                                      tr("Choose card first."));
    }
    else{
        QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size:20px}");
            msgBox.setText("Credit card ordered successfully.");
            msgBox.exec();
    }

}


void MainWindow::on_cards_american_bill_pay_now_button_clicked()
{

    pay_card_int = ui->cards_american_due_bill->text().toInt();


        QSqlQuery query;
        query.exec(" SELECT balance FROM user WHERE email = '"+current_user+"'");
        query.next();
            if(c_balance_int >= pay_card_int){
                c_balance_int = c_balance_int - pay_card_int;

                QSqlQuery query;
                query.prepare("UPDATE user SET balance=:balance WHERE email = '"+current_user+"'");
                query.bindValue(":balance", c_balance_int);
                query.exec();
                query.next();
                ui->cards_american_due_bill->setText("00.00");
                QMessageBox msgBox;
                    msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size:20px}");
                    msgBox.setText("Credit Card bill paid successfully.");
                    msgBox.exec();
}
            else{
                QMessageBox::warning(this, tr("Card"),
                                              tr("Insufficient Balance."));
            }
    }



void MainWindow::on_pushButton_clicked()
{
    pay_bill_int = ui->lineEdit_10->text().toInt();
    if(ui->comboBox_6->currentText() == "Choose Bill Type"  && pay_bill_int == NULL){
        QMessageBox::warning(this, tr("Utility Bill"),
                                      tr("Choose an option."));
    }
    else{
        QSqlQuery query;
        query.exec(" SELECT balance FROM user WHERE email = '"+current_user+"'");
        query.next();
            if(c_balance_int >= pay_bill_int){
                c_balance_int = c_balance_int - pay_bill_int;

                QSqlQuery query;
                query.prepare("UPDATE user SET balance=:balance WHERE email = '"+current_user+"'");
                query.bindValue(":balance", c_balance_int);
                query.exec();
                query.next();
                ui->lineEdit_10->clear();
                c_date = QDate::currentDate().toString("dd-MM-yyyy");
                    pay_bill = QString::number(pay_bill_int);

                    c_time = QTime::currentTime().toString("hh:mm AP");

                    QSqlQuery query1;
                    query1.exec("INSERT INTO 'main'.'transaction' (email, status, date, amount, time) "
                                "VALUES ('"+current_user+"', 'Utility Bill', '"+c_date+"', '"+pay_bill+"', '"+c_time+"')");
                    query1.next();

                    QMessageBox msgBox;
                        msgBox.setStyleSheet("QLabel{min-width: 500px; min-height: 100px; font-size:20px}");
                        msgBox.setText("BDT "+pay_bill+ "\n""Utility bill successfully paid\n");
                        msgBox.exec();
}
            else{
                QMessageBox::warning(this, tr("Utility Bill"),
                                              tr("Insufficient Balance."));
            }
}
}


void MainWindow::on_pushButton_2_clicked()
{
    pay_bill_int = ui->lineEdit_11->text().toInt();

    if(ui->comboBox_7->currentText() == "Choose Mobile Operator"  && pay_bill_int == NULL){
        QMessageBox::warning(this, tr("Mobile Recharge"),
                                      tr("Choose an option."));
    }
    else{
        QSqlQuery query;
        query.exec(" SELECT balance FROM user WHERE email = '"+current_user+"'");
        query.next();
            if(c_balance_int >= pay_bill_int){
                c_balance_int = c_balance_int - pay_bill_int;

                QSqlQuery query;
                query.prepare("UPDATE user SET balance=:balance WHERE email = '"+current_user+"'");
                query.bindValue(":balance", c_balance_int);
                query.exec();
                query.next();
                ui->lineEdit_10->clear();
                c_date = QDate::currentDate().toString("dd-MM-yyyy");
                    pay_bill = QString::number(pay_bill_int);

                    c_time = QTime::currentTime().toString("hh:mm AP");

                    QSqlQuery query1;
                    query1.exec("INSERT INTO 'main'.'transaction' (email, status, date, amount, time) "
                                "VALUES ('"+current_user+"', 'Recharge', '"+c_date+"', '"+pay_bill+"', '"+c_time+"')");
                    query1.next();

                    QMessageBox msgBox;
                        msgBox.setStyleSheet("QLabel{min-width: 500px; min-height: 100px; font-size:20px}");
                        msgBox.setText("Taka "+pay_bill+ "\n""Successfully recharged to the phone\n");
                        msgBox.exec();
}
            else{
                QMessageBox::warning(this, tr("Mobile recharge"),
                                              tr("Insufficient Balance."));
            }
}
}


void MainWindow::on_pushButton_3_clicked()
{
    pay_bill_int = ui->lineEdit_12->text().toInt();

    if(ui->comboBox_8->currentText() == "Choose Mobile Bank Account Type" && pay_bill_int == NULL){
        QMessageBox::warning(this, tr("Mobile Bank"),
                                      tr("Choose an option."));
    }
    else{
        QSqlQuery query;
        query.exec(" SELECT balance FROM user WHERE email = '"+current_user+"'");
        query.next();
            if(c_balance_int >= pay_bill_int){
                c_balance_int = c_balance_int - pay_bill_int;

                QSqlQuery query;
                query.prepare("UPDATE user SET balance=:balance WHERE email = '"+current_user+"'");
                query.bindValue(":balance", c_balance_int);
                query.exec();
                query.next();
                ui->lineEdit_10->clear();
                c_date = QDate::currentDate().toString("dd-MM-yyyy");
                    pay_bill = QString::number(pay_bill_int);

                    c_time = QTime::currentTime().toString("hh:mm AP");

                    QSqlQuery query1;
                    query1.exec("INSERT INTO 'main'.'transaction' (email, status, date, amount, time) "
                                "VALUES ('"+current_user+"', 'Mobile bank', '"+c_date+"', '"+pay_bill+"', '"+c_time+"')");
                    query1.next();

                    QMessageBox msgBox;
                        msgBox.setStyleSheet("QLabel{min-width: 500px; min-height: 100px; font-size:20px}");
                        msgBox.setText("Taka "+pay_bill+ "\n""Successfully sent\n");
                        msgBox.exec();
}
            else{
                QMessageBox::warning(this, tr("Mobile recharge"),
                                              tr("Insufficient Balance."));
            }
}
}

