#include <iostream>
#include <vector>

// 基类：图元
class Shape {
public:
    virtual void draw() = 0; // 绘制图元
};

// 点类
class Point : public Shape {
public:
    void draw() override {
        std::cout << "绘制点" << std::endl;
    }
};

// 折线类
class Polyline : public Shape {
public:
    void draw() override {
        std::cout << "绘制折线" << std::endl;
    }
};

// 多边形类
class Polygon : public Shape {
public:
    void draw() override {
        std::cout << "绘制多边形" << std::endl;
    }
};

// 矩形类
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "绘制矩形" << std::endl;
    }
};

// 圆类
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "绘制圆" << std::endl;
    }
};

// 扇形类
class Sector : public Shape {
public:
    void draw() override {
        std::cout << "绘制扇形" << std::endl;
    }
};

// 文本类
class Text : public Shape {
public:
    void draw() override {
        std::cout << "绘制文本" << std::endl;
    }
};

// 位图类
class Bitmap : public Shape {
public:
    void draw() override {
        std::cout << "绘制位图" << std::endl;
    }
};

// 抽象存储工厂
class StorageFactory {
public:
    virtual void save(const std::vector<Shape*>& shapes) = 0;
    virtual std::vector<Shape*> load() = 0;
};

// 文件存储工厂
class FileStorageFactory : public StorageFactory {
public:
    void save(const std::vector<Shape*>& shapes) override {
        // 实现文件存储逻辑
        std::cout << "将图形数据保存到文件" << std::endl;
    }

    std::vector<Shape*> load() override {
        // 实现文件加载逻辑
        std::cout << "从文件中加载图形数据" << std::endl;
        return std::vector<Shape*>();
    }
};

// 数据库存储工厂
class DatabaseStorageFactory : public StorageFactory {
public:
    void save(const std::vector<Shape*>& shapes) override {
        // 实现数据库存储逻辑
        std::cout << "将图形数据保存到数据库" << std::endl;
    }

    std::vector<Shape*> load() override {
        // 实现数据库加载逻辑
        std::cout << "从数据库中加载图形数据" << std::endl;
        return std::vector<Shape*>();
    }
};

// 图形管理类
class GraphicsManager {
private:
    std::vector<Shape*> shapes; // 存储图元的容器
    StorageFactory* storageFactory; // 存储工厂

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
