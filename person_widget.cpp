#include "person_widget.h"
#include "ui_person_widget.h"
#include<widget.h>
#include<qsqlquery.h>
extern QSqlDatabase db;
extern bool regestered;
extern bool is_admin;
extern QString ID;
extern QString username;
extern QString password;
person_widget::person_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::person_widget)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("个人信息",this);
    head->move(440,40);
    comboBox_type=new QComboBox(this);
    comboBox_type->addItems(QStringList()<<"居民身份证"<<"港澳通行证"<<"护照");
    comboBox_type->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    comboBox_type->installEventFilter(this);
    comboBox_type->move(480,375);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_return=new superButton("返回",this);btn_return->resize(250,40);
    btn_logout=new superButton("退出登录",this);btn_logout->resize(250,40);
    btn_commit->move(100,650);btn_return->move(400,650);btn_logout->move(700,650);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    btn_return->setMouseOutColor(QColor(4,186,251));
    btn_logout->setMouseOutColor(QColor(4,186,251));
    ui->userid->setReadOnly(true);
    this->setStyleSheet("QLineEdit{border :1px ;background-color: rgba(0,0,0,0)}");
    ui->groupBox->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
    connect(btn_commit,&superButton::Clicked,[=](){
        update();
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
    connect(btn_return,&superButton::Clicked,[=](){
        initialize();
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
    connect(btn_logout,&superButton::Clicked,[=](){
        QFile f(QApplication::applicationDirPath()+"/userinfo.dat");
        f.remove();
        regestered=false;
        is_admin=false;
        ID="";
        password="";
        username="";
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
}


person_widget::~person_widget()
{
    delete ui;
}

void person_widget::initialize()
{
    ui->userid->setText(ID);
    QString name_str,username_str,sex_str,telephone_str,credit_type,address,credit_id,beian;
    QString str = QString("select name,username,sex,telephone,credit_type,address,credit_id,for_reference from user where account_id='%1'").arg(ID);
    QSqlQuery query(db);
    query.exec(str);
    while(query.next())
    {
        name_str=query.value(0).toString();
        username_str=query.value(1).toString();
        sex_str=query.value(2).toString();
        telephone_str=query.value(3).toString();
        credit_type=query.value(4).toString();
        address=query.value(5).toString();
        credit_id=query.value(6).toString();
        beian=query.value(7).toString();
    }
    ui->phonenum->setText(telephone_str);
    ui->username->setText(username_str);
    ui->truename->setText(name_str);
    ui->address->setText(address);
    ui->beian->setText(beian);
    ui->idnum->setText(credit_id);
    ui->radioButton_2->setChecked(false);
    ui->radioButton->setChecked(false);
    if(sex_str=="男")ui->radioButton->setChecked(true);
    if(sex_str=="女")ui->radioButton_2->setChecked(true);
    if(credit_type=="居民身份证")comboBox_type->setCurrentIndex(0);
    if(credit_type=="港澳通行证")comboBox_type->setCurrentIndex(1);
    if(credit_type=="护照")comboBox_type->setCurrentIndex(2);
}
void person_widget::update()
{
    QString name_str,username_str,sex_str,telephone_str,credit_type,address,credit_id,beian;
    QString name_str1,username_str1,sex_str1,telephone_str1,credit_type1,address1,credit_id1,beian1;
    QString str = QString("select name,sex,telephone,credit_type,address,credit_id,for_reference from user where account_id='%1'").arg(ID);
    QSqlQuery query(db);
    query.exec(str);
    while(query.next())
    {
        name_str=query.value(0).toString();
        username_str=query.value(1).toString();
        sex_str=query.value(2).toString();
        telephone_str=query.value(3).toString();
        credit_type=query.value(4).toString();
        address=query.value(5).toString();
        credit_id=query.value(6).toString();
        beian=query.value(7).toString();
    }
    name_str1=ui->truename->text();
    username_str1=ui->username->text();
    if(ui->radioButton->isChecked())sex_str1="男";
    if(ui->radioButton_2->isChecked())sex_str1="女";
    telephone_str1=ui->phonenum->text();
    if(comboBox_type->currentIndex()==0)credit_type1="居民身份证";
    if(comboBox_type->currentIndex()==1)credit_type1="港澳通行证";
    if(comboBox_type->currentIndex()==2)credit_type1="护照";
    address1=ui->address->text();
    credit_id1=ui->idnum->text();
    beian1=ui->beian->text();
    if(username_str!=username_str1||name_str!=name_str1||sex_str!=sex_str1||telephone_str!=telephone_str1||credit_id!=credit_id1||credit_type!=credit_type1||address!=address1||beian!=beian1)
    {
        QString str1=QString("update user set name='%1',sex='%2',telephone='%3',credit_type='%4',address='%5',credit_id='%6',for_reference='%7',username='%9' where account_id='%8' ").arg(name_str1).arg(sex_str1).arg(telephone_str1).arg(credit_type1).arg(address1).arg(credit_id1).arg(beian1).arg(ID).arg(username_str1);
        query.exec(str1);
    }
}
bool person_widget::eventFilter(QObject* obj,QEvent* e)
{
    if(obj==comboBox_type&&e->type()==QEvent::MouseMove)
    return true;
    return false;
}
