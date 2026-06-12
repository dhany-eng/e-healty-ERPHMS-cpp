#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <limits>
#include <ctime>

using namespace std;

// ==================== FUNGSI TAMPILAN KONSOL ====================

// Mengatur warna teks di terminal
void setColor(int kodeWarna) {
    cout << "\033[" << kodeWarna << "m";
}

// Membersihkan buffer input setelah membaca angka
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Membaca pilihan menu dengan validasi range
int getChoice(int min, int max) {
    int pilihan;
    while (true) {
        cout << "Pilihan: ";
        if (cin >> pilihan) {
            if (pilihan >= min && pilihan <= max) {
                clearInputBuffer();
                return pilihan;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        setColor(31);
        cout << "Input tidak valid. Masukkan angka antara " << min << " dan " << max << ".\n";
        setColor(0);
    }
}

// Membersihkan layar terminal (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Mencetak garis pemisah
void printSeparator(char ch = '=', int length = 70) {
    for (int i = 0; i < length; i++) cout << ch;
    cout << endl;
}

// Mencetak judul header
void printHeader(const string& judul) {
    setColor(36);
    printSeparator('=', 70);
    cout << "          " << judul << endl;
    printSeparator('=', 70);
    setColor(0);
}

// Mencetak sub judul
void printSubHeader(const string& subJudul) {
    setColor(33);
    cout << "\n--- " << subJudul << " ---\n";
    setColor(0);
}

// Menunggu user menekan Enter
void waitForEnter() {
    cout << "\nTekan Enter untuk melanjutkan...";
    clearInputBuffer();
    cin.get();
}

// ==================== DATA MASTER (ARRAY DOKTER & OBAT) ====================

const int MAX_DOCTORS = 20;
const int MAX_MEDICINES = 30;

struct Doctor {
    int id;
    string name;
    string specialization;
};

struct Medicine {
    int id;
    string name;
    double price;
};

Doctor doctors[MAX_DOCTORS];
int doctorCount = 0;

Medicine medicines[MAX_MEDICINES];
int medicineCount = 0;

// Inisialisasi data awal dokter dan obat
void initMasterData() {
    doctorCount = 5;
    doctors[0] = {1, "Dr. Andi Wijaya", "Jantung"};
    doctors[1] = {2, "Dr. Budi Santoso", "Saraf"};
    doctors[2] = {3, "Dr. Citra Dewi", "Anak"};
    doctors[3] = {4, "Dr. Dian Pratama", "Umum"};
    doctors[4] = {5, "Dr. Eka Putri", "Bedah"};

    medicineCount = 8;
    medicines[0] = {1, "Paracetamol", 5000};
    medicines[1] = {2, "Amoxicillin", 15000};
    medicines[2] = {3, "Ibuprofen", 10000};
    medicines[3] = {4, "Omeprazole", 12000};
    medicines[4] = {5, "Cetirizine", 8000};
    medicines[5] = {6, "Ranitidine", 9000};
    medicines[6] = {7, "Dextromethorphan", 11000};
    medicines[7] = {8, "Vitamin C", 3000};
}

// Menampilkan daftar dokter
void displayDoctors() {
    if (doctorCount == 0) {
        cout << "Belum ada dokter.\n";
        return;
    }
    printSeparator('-', 70);
    cout << left << setw(5) << "ID" << setw(25) << "Nama Dokter" << setw(25) << "Spesialisasi" << endl;
    printSeparator('-', 70);
    for (int i = 0; i < doctorCount; i++) {
        cout << setw(5) << doctors[i].id
             << setw(25) << doctors[i].name
             << setw(25) << doctors[i].specialization << endl;
    }
    printSeparator('-', 70);
}

// Menampilkan daftar obat
void displayMedicines() {
    if (medicineCount == 0) {
        cout << "Belum ada obat.\n";
        return;
    }
    printSeparator('-', 70);
    cout << left << setw(5) << "ID" << setw(30) << "Nama Obat" << setw(15) << "Harga (Rp)" << endl;
    printSeparator('-', 70);
    for (int i = 0; i < medicineCount; i++) {
        cout << setw(5) << medicines[i].id
             << setw(30) << medicines[i].name
             << setw(15) << medicines[i].price << endl;
    }
    printSeparator('-', 70);
}

// Menambah dokter
void addDoctor() {
    if (doctorCount >= MAX_DOCTORS) {
        setColor(31); cout << "Kapasitas dokter penuh!\n"; setColor(0);
        return;
    }
    Doctor d;
    d.id = doctorCount + 1;
    clearInputBuffer();
    cout << "Nama dokter: "; getline(cin, d.name);
    cout << "Spesialisasi: "; getline(cin, d.specialization);
    doctors[doctorCount++] = d;
    setColor(32); cout << "Dokter berhasil ditambahkan! ID: " << d.id << endl; setColor(0);
}

// Menghapus dokter
void deleteDoctor() {
    if (doctorCount == 0) {
        cout << "Belum ada dokter.\n";
        return;
    }
    int id;
    cout << "Masukkan ID dokter yang akan dihapus: "; cin >> id;
    int idx = -1;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        setColor(31); cout << "Dokter tidak ditemukan.\n"; setColor(0);
        return;
    }
    cout << "Dokter: " << doctors[idx].name << " (ID: " << doctors[idx].id << ")\n";
    cout << "Yakin ingin menghapus? (y/n): ";
    char confirm; cin >> confirm;
    if (tolower(confirm) != 'y') {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }
    for (int i = idx; i < doctorCount - 1; i++) {
        doctors[i] = doctors[i + 1];
    }
    doctorCount--;
    setColor(32); cout << "Dokter berhasil dihapus.\n"; setColor(0);
}

// Mengubah data dokter
void updateDoctor() {
    if (doctorCount == 0) { cout << "Belum ada dokter.\n"; return; }
    int id;
    cout << "Masukkan ID dokter yang akan diubah: "; cin >> id;
    int idx = -1;
    for (int i = 0; i < doctorCount; i++) if (doctors[i].id == id) { idx = i; break; }
    if (idx == -1) { setColor(31); cout << "Dokter tidak ditemukan.\n"; setColor(0); return; }
    clearInputBuffer();
    cout << "Nama baru: "; getline(cin, doctors[idx].name);
    cout << "Spesialisasi baru: "; getline(cin, doctors[idx].specialization);
    setColor(32); cout << "Data dokter berhasil diubah.\n"; setColor(0);
}

// Menambah obat
void addMedicine() {
    if (medicineCount >= MAX_MEDICINES) {
        setColor(31); cout << "Kapasitas obat penuh!\n"; setColor(0);
        return;
    }
    Medicine m;
    m.id = medicineCount + 1;
    clearInputBuffer();
    cout << "Nama obat: "; getline(cin, m.name);
    cout << "Harga: Rp "; cin >> m.price;
    medicines[medicineCount++] = m;
    setColor(32); cout << "Obat berhasil ditambahkan! ID: " << m.id << endl; setColor(0);
}

// Menghapus obat
void deleteMedicine() {
    if (medicineCount == 0) {
        cout << "Belum ada obat.\n";
        return;
    }
    int id;
    cout << "Masukkan ID obat yang akan dihapus: "; cin >> id;
    int idx = -1;
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        setColor(31); cout << "Obat tidak ditemukan.\n"; setColor(0);
        return;
    }
    cout << "Obat: " << medicines[idx].name << " (ID: " << medicines[idx].id << ")\n";
    cout << "Yakin ingin menghapus? (y/n): ";
    char confirm; cin >> confirm;
    if (tolower(confirm) != 'y') {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }
    for (int i = idx; i < medicineCount - 1; i++) {
        medicines[i] = medicines[i + 1];
    }
    medicineCount--;
    setColor(32); cout << "Obat berhasil dihapus.\n"; setColor(0);
}

// Mengubah data obat
void updateMedicine() {
    if (medicineCount == 0) { cout << "Belum ada obat.\n"; return; }
    int id;
    cout << "Masukkan ID obat yang akan diubah: "; cin >> id;
    int idx = -1;
    for (int i = 0; i < medicineCount; i++) if (medicines[i].id == id) { idx = i; break; }
    if (idx == -1) { setColor(31); cout << "Obat tidak ditemukan.\n"; setColor(0); return; }
    clearInputBuffer();
    cout << "Nama baru: "; getline(cin, medicines[idx].name);
    cout << "Harga baru: Rp "; cin >> medicines[idx].price;
    setColor(32); cout << "Data obat berhasil diubah.\n"; setColor(0);
}

// ==================== STRUCT PASIEN ====================
struct Patient {
    int id;
    string name;
    int age;
    string diagnosis;
    int priority;   // 1=kritis, 2=sedang, 3=ringan
    Patient* next;
};

// ==================== PRIORITY QUEUE (ANTRIAN PASIEN) ====================
class PatientQueue {
private:
    Patient* front;
    Patient* rear;
public:
    PatientQueue() : front(nullptr), rear(nullptr) {}

    // Memasukkan pasien ke antrian berdasarkan prioritas
    void enqueue(int id, string name, int age, int priority, string diagnosis) {
        Patient* newNode = new Patient{id, name, age, diagnosis, priority, nullptr};
        if (isEmpty()) {
            front = rear = newNode;
            return;
        }
        if (priority < front->priority) {
            newNode->next = front;
            front = newNode;
            return;
        }
        Patient* current = front;
        while (current->next != nullptr && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == nullptr) rear = newNode;
    }
    
    // Mengeluarkan pasien dari depan antrian (prioritas tertinggi)
    Patient* dequeue() {
        if (isEmpty()) return nullptr;
        Patient* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        return temp;
    }
    
    bool isEmpty() { return front == nullptr; }
    
    // Menampilkan seluruh antrian
    void display() {
        if (isEmpty()) {
            cout << "Antrian kosong.\n";
            return;
        }
        Patient* current = front;
        int no = 1;
        printSeparator('-', 70);
        cout << left << setw(4) << "No" << setw(6) << "ID" << setw(20) << "Nama"
             << setw(10) << "Prioritas" << setw(20) << "Diagnosa" << endl;
        printSeparator('-', 70);
        while (current) {
            string prio = (current->priority == 1) ? "KRITIS" : (current->priority == 2) ? "SEDANG" : "RINGAN";
            cout << setw(4) << no++ << setw(6) << current->id << setw(20) << current->name
                 << setw(10) << prio << setw(20) << current->diagnosis << endl;
            current = current->next;
        }
        printSeparator('-', 70);
    }
    
    // Mengupdate nama pasien di antrian jika masih ada
    bool updatePatientName(int id, const string& newName) {
        Patient* current = front;
        while (current) {
            if (current->id == id) {
                current->name = newName;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Menghapus pasien dari antrian berdasarkan ID
    bool removePatientById(int id) {
        if (isEmpty()) return false;
        if (front->id == id) {
            Patient* temp = front;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            delete temp;
            return true;
        }
        Patient* prev = front;
        Patient* curr = front->next;
        while (curr) {
            if (curr->id == id) {
                prev->next = curr->next;
                if (curr->next == nullptr) rear = prev;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }
};

// ==================== STACK (RIWAYAT KUNJUNGAN - LIFO) ====================
class VisitHistoryStack {
private:
    struct StackNode {
        int patientId;
        string patientName;
        string visitTime;
        StackNode* next;
    };
    StackNode* top;
public:
    VisitHistoryStack() : top(nullptr) {}
    
    // Push (dorong) ke stack
    void push(int id, string name, string time) {
        StackNode* newNode = new StackNode{id, name, time, top};
        top = newNode;
    }
    
    // Pop (keluarkan) dari stack
    void pop() {
        if (!isEmpty()) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    bool isEmpty() { return top == nullptr; }
    
    // Tampilkan semua riwayat (dari yang terbaru ke lama)
    void display() {
        if (isEmpty()) {
            cout << "Tumpukan riwayat kosong.\n";
            return;
        }
        StackNode* current = top;
        int no = 1;
        printSeparator('-', 70);
        cout << left << setw(4) << "No" << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Waktu Kunjungan" << endl;
        printSeparator('-', 70);
        while (current) {
            cout << setw(4) << no++ << setw(8) << current->patientId << setw(20) << current->patientName
                 << setw(20) << current->visitTime << endl;
            current = current->next;
        }
        printSeparator('-', 70);
    }
    
    // Hapus semua catatan riwayat untuk pasien tertentu
    void removeByPatientId(int id) {
        while (top && top->patientId == id) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
        if (!top) return;
        StackNode* curr = top;
        while (curr->next) {
            if (curr->next->patientId == id) {
                StackNode* temp = curr->next;
                curr->next = temp->next;
                delete temp;
            } else {
                curr = curr->next;
            }
        }
    }
};

// ==================== LINKED LIST (RIWAYAT MEDIS) ====================
class MedicalHistoryList {
private:
    struct MedicalNode {
        int patientId;
        string visitDate;
        string diagnosis;
        string treatment;
        MedicalNode* next;
    };
    MedicalNode* head;
public:
    MedicalHistoryList() : head(nullptr) {}
    
    // Tambahkan riwayat medis baru (di awal list)
    void addHistory(int patientId, string date, string diagnosis, string treatment) {
        MedicalNode* newNode = new MedicalNode{patientId, date, diagnosis, treatment, head};
        head = newNode;
    }
    
    // Tampilkan semua riwayat medis untuk satu pasien
    void displayHistory(int patientId) {
        MedicalNode* curr = head;
        bool found = false;
        cout << "Riwayat medis pasien ID " << patientId << ":\n";
        printSeparator('-', 70);
        while (curr) {
            if (curr->patientId == patientId) {
                cout << "Tanggal: " << curr->visitDate << "\nDiagnosa: " << curr->diagnosis
                     << "\nPengobatan: " << curr->treatment << "\n";
                printSeparator('-', 70);
                found = true;
            }
            curr = curr->next;
        }
        if (!found) cout << "Tidak ada riwayat.\n";
    }
    
    // Hapus semua riwayat pasien berdasarkan ID
    void removeByPatientId(int id) {
        while (head && head->patientId == id) {
            MedicalNode* temp = head;
            head = head->next;
            delete temp;
        }
        if (!head) return;
        MedicalNode* curr = head;
        while (curr->next) {
            if (curr->next->patientId == id) {
                MedicalNode* temp = curr->next;
                curr->next = temp->next;
                delete temp;
            } else {
                curr = curr->next;
            }
        }
    }
};

// ==================== BINARY SEARCH TREE (INDEKS PASIEN BERDASARKAN ID) ====================
class PatientBST {
private:
    struct TreeNode {
        Patient* patient;
        TreeNode* left;
        TreeNode* right;
        TreeNode(Patient* p) : patient(p), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;
    
    // Sisip node secara rekursif
    TreeNode* insert(TreeNode* node, Patient* patient) {
        if (!node) return new TreeNode(patient);
        if (patient->id < node->patient->id)
            node->left = insert(node->left, patient);
        else if (patient->id > node->patient->id)
            node->right = insert(node->right, patient);
        return node;
    }
    
    // Cari node berdasarkan ID (rekursif)
    TreeNode* search(TreeNode* node, int id) {
        if (!node || node->patient->id == id) return node;
        if (id < node->patient->id) return search(node->left, id);
        else return search(node->right, id);
    }
    
    // Traversal inorder untuk menghasilkan string terurut
    void inorder(TreeNode* node, string& result) {
        if (node) {
            inorder(node->left, result);
            result += "ID: " + to_string(node->patient->id) + " | Nama: " + node->patient->name +
                      " | Umur: " + to_string(node->patient->age) + " | Diagnosa: " + node->patient->diagnosis + "\n";
            inorder(node->right, result);
        }
    }
    
    // Hapus node (rekursif) dengan 3 kasus
    TreeNode* deleteNode(TreeNode* node, int id) {
        if (!node) return nullptr;
        if (id < node->patient->id)
            node->left = deleteNode(node->left, id);
        else if (id > node->patient->id)
            node->right = deleteNode(node->right, id);
        else {
            // Kasus 1: tidak punya anak kiri
            if (!node->left) {
                TreeNode* right = node->right;
                delete node->patient;
                delete node;
                return right;
            }
            // Kasus 2: tidak punya anak kanan
            if (!node->right) {
                TreeNode* left = node->left;
                delete node->patient;
                delete node;
                return left;
            }
            // Kasus 3: punya dua anak -> cari successor
            TreeNode* successor = node->right;
            while (successor->left) successor = successor->left;
            // Salin data dari successor ke node
            node->patient->id = successor->patient->id;
            node->patient->name = successor->patient->name;
            node->patient->age = successor->patient->age;
            node->patient->diagnosis = successor->patient->diagnosis;
            node->patient->priority = successor->patient->priority;
            // Hapus successor
            node->right = deleteNode(node->right, successor->patient->id);
        }
        return node;
    }
    
    // Bersihkan seluruh pohon (rekursif)
    void clear(TreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node->patient;
            delete node;
        }
    }
    
public:
    PatientBST() : root(nullptr) {}
    ~PatientBST() { clear(root); }
    
    void addPatient(Patient* patient) {
        root = insert(root, patient);
    }
    
    Patient* findPatient(int id) {
        TreeNode* res = search(root, id);
        return res ? res->patient : nullptr;
    }
    
    string getAllPatientsString() {
        string result;
        inorder(root, result);
        if (result.empty()) result = "Belum ada pasien.";
        return result;
    }
    
    void displayAll() {
        cout << getAllPatientsString();
    }
    
    bool updatePatientName(int id, const string& newName) {
        Patient* p = findPatient(id);
        if (p) {
            p->name = newName;
            return true;
        }
        return false;
    }
    
    bool deletePatient(int id) {
        if (!findPatient(id)) return false;
        root = deleteNode(root, id);
        return true;
    }
};

// ==================== OBJEK GLOBAL ====================
PatientQueue waitingQueue;
VisitHistoryStack visitStack;
MedicalHistoryList medHistory;
PatientBST patientBST;
int nextPatientId = 1001;

// Mendapatkan waktu saat ini dalam bentuk string
string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string s(dt);
    s.pop_back(); // hapus newline
    return s;
}

// ==================== FITUR PASIEN ====================
void addPatient() {
    clearScreen();
    printHeader("TAMBAH PASIEN BARU");
    string name, diagnosis;
    int age, priority;
    clearInputBuffer();
    cout << "Nama Pasien : "; getline(cin, name);
    cout << "Umur        : "; cin >> age;
    cout << "Prioritas (1=KRITIS, 2=SEDANG, 3=RINGAN): "; cin >> priority;
    clearInputBuffer();
    cout << "Diagnosa    : "; getline(cin, diagnosis);
    
    Patient* newPatient = new Patient{nextPatientId, name, age, diagnosis, priority, nullptr};
    patientBST.addPatient(newPatient);
    waitingQueue.enqueue(nextPatientId, name, age, priority, diagnosis);
    
    setColor(32);
    cout << "\n✅ Pasien " << name << " (ID: " << nextPatientId << ") berhasil ditambahkan ke antrian!\n";
    setColor(0);
    nextPatientId++;
    waitForEnter();
}

void viewQueue() {
    clearScreen();
    printSubHeader("ANTRIAN PASIEN SAAT INI (PRIORITAS TERTINGGI DI DEPAN)");
    waitingQueue.display();
    waitForEnter();
}

void servePatient() {
    clearScreen();
    printHeader("LAYANI PASIEN");
    if (waitingQueue.isEmpty()) {
        cout << "Tidak ada pasien dalam antrian.\n";
        waitForEnter();
        return;
    }
    Patient* served = waitingQueue.dequeue();
    string time = getCurrentTime();
    visitStack.push(served->id, served->name, time);
    medHistory.addHistory(served->id, time, served->diagnosis, "Dalam perawatan");
    
    setColor(32);
    cout << "Pasien dengan ID " << served->id << " (" << served->name << ") telah dilayani.\n";
    cout << "Waktu kunjungan: " << time << endl;
    setColor(0);
    waitForEnter();
}

void updatePatientName() {
    clearScreen();
    printHeader("UBAH NAMA PASIEN");
    int id;
    cout << "Masukkan ID pasien: "; cin >> id;
    Patient* p = patientBST.findPatient(id);
    if (!p) {
        setColor(31); cout << "Pasien tidak ditemukan!\n"; setColor(0);
        waitForEnter();
        return;
    }
    cout << "Nama lama: " << p->name << endl;
    string newName;
    clearInputBuffer();
    cout << "Nama baru: "; getline(cin, newName);
    
    patientBST.updatePatientName(id, newName);
    waitingQueue.updatePatientName(id, newName);
    setColor(32); cout << "Nama berhasil diubah menjadi " << newName << endl; setColor(0);
    waitForEnter();
}

void deletePatient() {
    clearScreen();
    printHeader("HAPUS PASIEN");
    int id;
    cout << "Masukkan ID pasien yang akan dihapus: "; cin >> id;
    Patient* p = patientBST.findPatient(id);
    if (!p) {
        setColor(31); cout << "Pasien tidak ditemukan!\n"; setColor(0);
        waitForEnter();
        return;
    }
    cout << "Data pasien:\n";
    cout << "ID: " << p->id << ", Nama: " << p->name << ", Umur: " << p->age << ", Diagnosa: " << p->diagnosis << endl;
    cout << "Yakin ingin menghapus pasien ini? (y/n): ";
    char confirm; cin >> confirm;
    if (tolower(confirm) != 'y') {
        cout << "Penghapusan dibatalkan.\n";
        waitForEnter();
        return;
    }
    bool deleted = patientBST.deletePatient(id);
    if (deleted) {
        waitingQueue.removePatientById(id);
        visitStack.removeByPatientId(id);
        medHistory.removeByPatientId(id);
        setColor(32); cout << "Pasien berhasil dihapus dari sistem (termasuk riwayat kunjungan dan medis).\n"; setColor(0);
    } else {
        setColor(31); cout << "Gagal menghapus pasien.\n"; setColor(0);
    }
    waitForEnter();
}

void searchPatient() {
    clearScreen();
    printHeader("CARI PASIEN BERDASARKAN ID");
    int id;
    cout << "ID Pasien: "; cin >> id;
    Patient* p = patientBST.findPatient(id);
    if (p) {
        setColor(36);
        cout << "\nData Pasien:\n";
        cout << "ID        : " << p->id << endl;
        cout << "Nama      : " << p->name << endl;
        cout << "Umur      : " << p->age << endl;
        cout << "Diagnosa  : " << p->diagnosis << endl;
        cout << "Prioritas : " << (p->priority == 1 ? "KRITIS" : (p->priority == 2 ? "SEDANG" : "RINGAN")) << endl;
        setColor(0);
    } else {
        setColor(31); cout << "Pasien tidak ditemukan.\n"; setColor(0);
    }
    waitForEnter();
}

void viewAllPatients() {
    clearScreen();
    printSubHeader("SEMUA PASIEN TERDAFTAR (URUTAN ID)");
    patientBST.displayAll();
    waitForEnter();
}

void viewVisitHistory() {
    clearScreen();
    printSubHeader("RIWAYAT KUNJUNGAN (STACK - TERAKHIR DI ATAS)");
    visitStack.display();
    waitForEnter();
}

void viewMedicalHistory() {
    clearScreen();
    printHeader("LIHAT RIWAYAT MEDIS PASIEN");
    int id;
    cout << "Masukkan ID Pasien: "; cin >> id;
    medHistory.displayHistory(id);
    waitForEnter();
}

// ==================== MENU UTAMA ====================
int main() {
    initMasterData();
    // Data awal untuk demo
    Patient* p1 = new Patient{1001, "John Doe", 45, "Demam Tinggi", 2, nullptr};
    Patient* p2 = new Patient{1002, "Jane Smith", 30, "Patah Tulang", 1, nullptr};
    patientBST.addPatient(p1);
    patientBST.addPatient(p2);
    waitingQueue.enqueue(1001, "John Doe", 45, 2, "Demam Tinggi");
    waitingQueue.enqueue(1002, "Jane Smith", 30, 1, "Patah Tulang");
    nextPatientId = 1003;
    medHistory.addHistory(1001, "2024-01-15 10:00", "Demam Tinggi", "Paracetamol");
    medHistory.addHistory(1002, "2024-01-16 14:30", "Patah Tulang", "Operasi");
    visitStack.push(1002, "Jane Smith", "2024-01-16 14:30");
    visitStack.push(1001, "John Doe", "2024-01-15 10:00");
    
    int choice;
    do {
        clearScreen();
        printHeader("ERPHMS - SISTEM MANAJEMEN GAWAT DARURAT");
        cout << "\n=== MANAJEMEN PASIEN ===\n";
        cout << "1. Tambah Pasien Baru\n";
        cout << "2. Lihat Antrian Pasien\n";
        cout << "3. Layani Pasien (Proses Antrian)\n";
        cout << "4. Ubah Nama Pasien\n";
        cout << "5. Hapus Pasien\n";
        cout << "6. Cari Pasien Berdasarkan ID\n";
        cout << "7. Lihat Semua Pasien (BST)\n";
        cout << "8. Lihat Riwayat Kunjungan (Stack)\n";
        cout << "9. Lihat Riwayat Medis Pasien (Linked List)\n";
        cout << "\n=== MANAJEMEN DOKTER ===\n";
        cout << "10. Lihat Daftar Dokter\n";
        cout << "11. Tambah Dokter\n";
        cout << "12. Ubah Data Dokter\n";
        cout << "13. Hapus Dokter\n";
        cout << "\n=== MANAJEMEN OBAT ===\n";
        cout << "14. Lihat Daftar Obat\n";
        cout << "15. Tambah Obat\n";
        cout << "16. Ubah Data Obat\n";
        cout << "17. Hapus Obat\n";
        cout << "\n0. Keluar\n";
        printSeparator('-', 50);
        
        choice = getChoice(0, 17);
        
        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewQueue(); break;
            case 3: servePatient(); break;
            case 4: updatePatientName(); break;
            case 5: deletePatient(); break;
            case 6: searchPatient(); break;
            case 7: viewAllPatients(); break;
            case 8: viewVisitHistory(); break;
            case 9: viewMedicalHistory(); break;
            case 10: clearScreen(); printSubHeader("DAFTAR DOKTER"); displayDoctors(); waitForEnter(); break;
            case 11: clearScreen(); printSubHeader("TAMBAH DOKTER"); addDoctor(); waitForEnter(); break;
            case 12: clearScreen(); printSubHeader("UBAH DATA DOKTER"); updateDoctor(); waitForEnter(); break;
            case 13: clearScreen(); printSubHeader("HAPUS DOKTER"); deleteDoctor(); waitForEnter(); break;
            case 14: clearScreen(); printSubHeader("DAFTAR OBAT"); displayMedicines(); waitForEnter(); break;
            case 15: clearScreen(); printSubHeader("TAMBAH OBAT"); addMedicine(); waitForEnter(); break;
            case 16: clearScreen(); printSubHeader("UBAH DATA OBAT"); updateMedicine(); waitForEnter(); break;
            case 17: clearScreen(); printSubHeader("HAPUS OBAT"); deleteMedicine(); waitForEnter(); break;
            case 0:
                cout << "\nTerima kasih telah menggunakan ERPHMS.\n";
                break;
        }
    } while (choice != 0);
    
    return 0;
}