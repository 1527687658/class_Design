#include <iostream>
#include <vector>

// ���ࣺͼԪ
class Shape {
public:
    virtual void draw() = 0; // ����ͼԪ
};

// ����
class Point : public Shape {
public:
    void draw() override {
        std::cout << "���Ƶ�" << std::endl;
    }
};

// ������
class Polyline : public Shape {
public:
    void draw() override {
        std::cout << "��������" << std::endl;
    }
};

// �������
class Polygon : public Shape {
public:
    void draw() override {
        std::cout << "���ƶ����" << std::endl;
    }
};

// ������
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "���ƾ���" << std::endl;
    }
};

// Բ��
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "����Բ" << std::endl;
    }
};

// ������
class Sector : public Shape {
public:
    void draw() override {
        std::cout << "��������" << std::endl;
    }
};

// �ı���
class Text : public Shape {
public:
    void draw() override {
        std::cout << "�����ı�" << std::endl;
    }
};

// λͼ��
class Bitmap : public Shape {
public:
    void draw() override {
        std::cout << "����λͼ" << std::endl;
    }
};

// ����洢����
class StorageFactory {
public:
    virtual void save(const std::vector<Shape*>& shapes) = 0;
    virtual std::vector<Shape*> load() = 0;
};

// �ļ��洢����
class FileStorageFactory : public StorageFactory {
public:
    void save(const std::vector<Shape*>& shapes) override {
        // ʵ���ļ��洢�߼�
        std::cout << "��ͼ�����ݱ��浽�ļ�" << std::endl;
    }

    std::vector<Shape*> load() override {
        // ʵ���ļ������߼�
        std::cout << "���ļ��м���ͼ������" << std::endl;
        return std::vector<Shape*>();
    }
};

// ���ݿ�洢����
class DatabaseStorageFactory : public StorageFactory {
public:
    void save(const std::vector<Shape*>& shapes) override {
        // ʵ�����ݿ�洢�߼�
        std::cout << "��ͼ�����ݱ��浽���ݿ�" << std::endl;
    }

    std::vector<Shape*> load() override {
        // ʵ�����ݿ�����߼�
        std::cout << "�����ݿ��м���ͼ������" << std::endl;
        return std::vector<Shape*>();
    }
};

// ͼ�ι�����
class GraphicsManager {
private:
    std::vector<Shape*> shapes; // �洢ͼԪ������
    StorageFactory* storageFactory; // �洢����

public:
    GraphicsManager(StorageFactory* factory) : storageFactory(factory) {}

    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }

    void saveShapes() {
        storageFactory->save(shapes);
    }

    void loadShapes() {
        shapes = storageFactory->load();
    }

    void drawAllShapes() {
        for (Shape* shape : shapes) {
            shape->draw();
        }
    }
};

int main() {
    StorageFactory* fileFactory = new FileStorageFactory();
    StorageFactory* databaseFactory = new DatabaseStorageFactory();

    GraphicsManager fileManager(fileFactory);
    fileManager.addShape(new Point());
    fileManager.addShape(new Polyline());
    fileManager.saveShapes();

    GraphicsManager databaseManager(databaseFactory);
    databaseManager.loadShapes();
    databaseManager.drawAllShapes();

    delete fileFactory;
    delete databaseFactory;

    return 0;
}
