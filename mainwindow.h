#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vector>
#include <Qstring>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_AddPatient_clicked();
    void on_btn_AddDoctor_clicked();
    void on_btn_ShowPatient_clicked();
    void on_btn_savedoctor_clicked();

    void on_btn_savepatient_clicked();



    void on_btn_ShowDoctor_clicked();

    void on_btn_Exit_clicked();



    void on_btn_login_clicked();

    void on_txt_searchpatient_textChanged(const QString &arg1);

    void on_btn_searchpatient_clicked();



private:
    Ui::MainWindow *ui;
    struct Patient {
        QString name;
        int age;
        QString gender;
        QString doctor;
        int id;
    };
    struct Doctor {
        QString name;
        QString specialization;
    };

    std::vector<Patient> patientsList; // مخزن المرضى
    std::vector<Doctor> doctorsList;   // مخزن الدكاترة (الجديد)

    void updateDoctorsComboBox(); // دالة التحديث
    void displayPatients();
    void displayDoctors();

};

#endif // MAINWINDOW_H
