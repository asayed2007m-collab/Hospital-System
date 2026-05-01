#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table_patient->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_doctors->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->table_searchpatient->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // هنفترض إن صفحة اللوجين الجديدة هي رقم 4 (آخر واحدة ضفتها)
    // إحنا هنقول للبرنامج: "أول ما تفتح، اظهر الصفحة رقم 4"
    ui->stackedWidget->setCurrentIndex(5);

    // وطبعاً نخفي المنيو عشان ميهربش منها
    ui->left_menu_frame->hide();

}

MainWindow::~MainWindow()
{
    delete ui;

}





void MainWindow::on_btn_AddPatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}



void MainWindow::updateDoctorsComboBox()
{

    ui->cmb_selectdoctor->clear(); // بيمسح القائمة القديمة

    // بيلف على كل الدكاترة اللي ضفناهم ويحطهم في القائمة
    for (const auto& doc : doctorsList) {
        ui->cmb_selectdoctor->addItem(doc.name + " (" + doc.specialization + ")");
    }
}






void MainWindow::on_btn_AddDoctor_clicked()
{

        ui->stackedWidget->setCurrentIndex(2); // سطر التبديل مكانه هنا جوه الزرار

}
void MainWindow::displayPatients()
{
    // 1. تصفير الجدول عشان لو ضفنا مريض جديد ميكررش القديم فوقه
    ui->table_patient->setRowCount(0);

    // 2. لفة على كل مريض في المخزن (Vector)
    for (int i = 0; i < patientsList.size(); i++) {
        // بنضيف صف جديد في الجدول

        ui->table_patient->insertRow(i);

        // بنحط البيانات في كل خانة (Row, Column)
        // زود السطر ده كأول سطر في عرض البيانات جوه الـ Loop
        ui->table_patient->setItem(i, 0, new QTableWidgetItem(QString::number(patientsList[i].id)));
        ui->table_patient->setItem(i, 1, new QTableWidgetItem(patientsList[i].name));
        ui->table_patient->setItem(i, 2, new QTableWidgetItem(QString::number(patientsList[i].age)));
        ui->table_patient->setItem(i, 3, new QTableWidgetItem(patientsList[i].gender));
        ui->table_patient->setItem(i, 4, new QTableWidgetItem(patientsList[i].doctor));

    }
}


void MainWindow::on_btn_ShowPatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // اقلب لصفحة الجدول (تأكد من الرقم)
    displayPatients(); // أهم سطر: شغل فانكشن العرض فوراً
}








void MainWindow::on_btn_savedoctor_clicked()
{

    Doctor newDoc;
    newDoc.name = ui->txt_DoctorName->text();
    newDoc.specialization = ui->cmb_DoctorSpec->currentText();

    if(newDoc.name.isEmpty()){
        return;
    }

    // 2. إضافة الدكتور للمخزن
    doctorsList.push_back(newDoc);

    // 3. تحديث قائمة الدكاترة في صفحة المريض فوراً
    updateDoctorsComboBox();

    // 4. مسح الخانات





    // السطر السحري للرسالة:
    QMessageBox::information(this, "نجاح", "تم حفظ بيانات الدكتور بنجاح! ✅");


    ui->txt_DoctorName->clear();
}


void MainWindow::on_btn_savepatient_clicked()
{
    Patient newPatient;
    newPatient.name = ui->txt_patientname->text();
    newPatient.age = ui->spn_patientage->value();
    newPatient.gender = ui->cmb_patientgender->currentText();
    newPatient.doctor = ui->cmb_selectdoctor->currentText();
    newPatient.id =ui->txt_patientid->text().toInt();

    if(!newPatient.name.isEmpty()) {
        patientsList.push_back(newPatient);
        QMessageBox::information(this, "Success", "تم الحفظ في قاعدة البيانات المؤقتة");
    }

    // ----- سطور مسح البيانات (تتحط هنا) -----
    ui->txt_patientname->clear(); // بيمسح النص اللي في خانة الاسم
    ui->txt_patientid->clear();
    ui->spn_patientage->setValue(0);        // بيرجع السن للقيمة الافتراضية (مثلاً 18)
    ui->cmb_patientgender->setCurrentIndex(0); // بيرجع اختيار النوع لأول عنصر
    ui->cmb_selectdoctor->setCurrentIndex(0); // بيرجع اختيار الدكتور لأول عنصر
}
void MainWindow::displayDoctors() {
    // 1. مسح الجدول القديم وتحديد عدد الصفوف بناءً على عدد الدكاترة
    ui->table_doctors->setRowCount(0);

    // 2. اللف على كل دكتور في الـ Vector
    for (int i = 0; i < doctorsList.size(); i++) {
        ui->table_doctors->insertRow(i); // إضافة صف جديد

        // إضافة اسم الدكتور في العمود الأول
        ui->table_doctors->setItem(i, 0, new QTableWidgetItem(doctorsList[i].name));

        // إضافة التخصص في العمود الثاني
        ui->table_doctors->setItem(i, 1, new QTableWidgetItem(doctorsList[i].specialization));


    }
}

void MainWindow::on_btn_ShowDoctor_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    displayDoctors();
}


void MainWindow::on_btn_Exit_clicked()
{



    // 1. السؤال الأول (تأكيد الخروج)
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "تأكيد الخروج",
                                  "هل أنت متأكد أنك تريد حفظ التغييرات والخروج؟",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 2. كود الحفظ (رقم 3 اللي إنت عاوزه)
        // هنا المفروض تنادي الفانكشن اللي بتبعت البيانات لملف أو قاعدة بيانات
        // لو لسه معملتهاش، ممكن نكتفي برسالة تأكيد إن الحفظ تم

        // مثال: saveAllDataToFile();



        // 3. الخروج الفعلي
        QApplication::quit();
    }
    // لو اختار No.. مبيحصلش حاجة والبرنامج بيفضل مفتوح عادي
}




void MainWindow::on_btn_login_clicked()
{


        QString username = ui->txt_username->text();
        QString password = ui->txt_password->text();

        if (username == "admin" && password == "1234") {
            // لو البيانات صح
            QMessageBox::information(this, "Login Success", "Welcome to Innovation university hospital system");
            ui->left_menu_frame->show();

            // هنا الكود اللي بيخفي صفحة اللوجين ويفتح صفحة البرنامج
            // لو إنت عاملهم في نفس الصفحة ممكن تستخدم QStackedWidget
            ui->stackedWidget->setCurrentIndex(0);

        } else {
            // لو البيانات غلط
            QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
        }

}


void MainWindow::on_txt_searchpatient_textChanged(const QString &arg1)
{


        // 1. لو الخانة فضيت، اظهر كل الصفوف تاني فوراً
        if (arg1.isEmpty()) {
            for (int i = 0; i < ui->table_searchpatient->rowCount(); i++) {
                ui->table_searchpatient->setRowHidden(i, false);
            }
            return;
        }

        // 2. بنلف على صفوف جدول البحث (table_search)
        for (int i = 0; i < ui->table_searchpatient->rowCount(); i++) {
            // بنجيب الـ ID من أول عمود (العمود رقم 0)
            QTableWidgetItem *item = ui->table_searchpatient->item(i, 0);

            if (item) {
                // بنشوف هل اللي كتبته (arg1) موجود جوه الـ ID؟
                // استخدمنا CaseInsensitive عشان لو فيه حروف أو رموز ميعلقش
                bool n = item->text().contains(arg1, Qt::CaseInsensitive);

                // التكة هنا: لو مش مطابق (match == false) يبقى Hidden (true)
                ui->table_searchpatient->setRowHidden(i, !n);
            }
        }

}


void MainWindow::on_btn_searchpatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
        ui->table_searchpatient->setRowCount(0);

    // 3. ابدأ انقل كل مريض من الـ Vector للجدول
    for (int i = 0; i < patientsList.size(); i++) {
        // بنضيف صف جديد في كل لفة

        ui->table_searchpatient->insertRow(i);

        // العمود 0: الـ ID (بنحوله لـ String عشان الجدول بيقبل نصوص)
        ui->table_searchpatient->setItem(i, 0, new QTableWidgetItem(QString::number(patientsList[i].id)));

        // العمود 1: الاسم
        ui->table_searchpatient->setItem(i, 1, new QTableWidgetItem(patientsList[i].name));

        // العمود 2: العمر (بنحوله لـ String برضه)
        ui->table_searchpatient->setItem(i, 2, new QTableWidgetItem(QString::number(patientsList[i].age)));

        // العمود 3: النوع (Gender)
        ui->table_searchpatient->setItem(i, 3, new QTableWidgetItem(patientsList[i].gender));

        // العمود 4: اسم الدكتور
        ui->table_searchpatient->setItem(i, 4, new QTableWidgetItem(patientsList[i].doctor));
    }

    displayPatients();
}




