#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>




class GeoShape 
{
public:
    virtual std::string merge() = 0;//整合属性，将属性写入文件
    virtual void read_picture() = 0;//将已绘制的图元设置到属性
    virtual void read_file(std::vector<int>) = 0;//读文件，并设置属性
    virtual void getcolor()=0;//获得画笔情况
    virtual void getproperty()=0;//获得设置参数
private:
    int color[4];
    int type;
    std::vector<int> m_pos;
};


class point :public GeoShape
{
public:

private:
    int color[4];
    int type;
    std::vector<int> m_pos;
    int size;//点的大小
};

class line :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;
    int size;//线宽
};

class polygon :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;
};

//drawRect(20,20,160,160); (左上角起点xy,长,宽)
class rectangle :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;//左上角起点xy
    int width;
    int height;
};
//drawEllipse(20,20,210,160);矩形左上角，长宽
class circle :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;//矩形左上角的点
    int width;
    int height;
};
//drawPie(rectangle, startAngle, spanAngle);
class sector :public GeoShape
{
public:
private:
    int color[4];
    int type;
    rectangle rec;
    int startangle;
    int spantangle;
};

class Non_GeoShape 
{
public:
    struct Point
    {
        int x, y;
    };
private:

    std::string content;
    Point pos;//放置的中心位置
};

class txt :public Non_GeoShape
{
public:

private:

    //p.setFont(QFont("微软雅黑", 15, 700, false));
    std::string style;//字体
    int size;//字体大小
    int blod;//粗体权重
    bool italic;//是否斜体

    //drawText(QPoint(20, 60), "分数:" + QString::number(score));
    Point pos;//放置位置
    std::string content;//内容
};


class Bitmap/* :public Non_GeoShape*/;
//{
//public:
//    Bitmap() : width(0), height(0) {}
//
//    friend void FileStorageFactory::save_bitmap(Bitmap& bit, const std::string& filename);
//
//    //打开位图bmp 读取信息
//    bool loadFromFile(const std::string& filename) {
//        std::ifstream file(filename, std::ios::binary);
//        if (!file) {
//            std::cout << "无法打开位图文件：" << filename << std::endl;
//            return false;
//        }
//
//        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
//        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
//
//        if (fileHeader.type != 0x4D42 || infoHeader.bitCount != 24) {
//            std::cout << "不支持的位图格式" << std::endl;
//            return false;
//        }
//
//        int padding = (4 - (infoHeader.width * 3) % 4) % 4;
//        pixels.resize(infoHeader.height * infoHeader.width);
//        for (int y = infoHeader.height - 1; y >= 0; y--) {
//            for (int x = 0; x < infoHeader.width; x++) {
//                uint8_t pixel[3];
//                file.read(reinterpret_cast<char*>(pixel), sizeof(pixel));
//                pixels[y * infoHeader.width + x] = { static_cast<int>(pixel[2]), static_cast<int>(pixel[1]), static_cast<int>(pixel[0]) };
//            }
//            file.ignore(padding);
//        }
//
//        width = infoHeader.width;
//        height = infoHeader.height;
//
//        return true;
//    }
//
//
//    bool saveAsText(const std::string& filename) {
//        std::ofstream file(filename);
//        if (!file) {
//            std::cout << "无法创建输出文件：" << filename << std::endl;
//            return false;
//        }
//
//        for (int y = height - 1; y >= 0; y--) {
//            for (int x = 0; x < width; x++) {
//                const Pixel& pixel = pixels[y * width + x];
//                file << pixel.red << " " << pixel.green << " " << pixel.blue << " ";
//            }
//            file << std::endl;
//        }
//
//        std::cout << "位图已保存为文本文件：" << filename << std::endl;
//        return true;
//    }
//
//    //打开位图txt
//    bool loadFromText(const std::string& filename) {
//        std::ifstream file(filename);
//        if (!file) {
//            std::cout << "无法打开文本文件：" << filename << std::endl;
//            return false;
//        }
//
//        std::vector<Pixel> loadedPixels;
//        std::string line;
//        while (std::getline(file, line)) {
//            std::istringstream iss(line);
//            int red, green, blue;
//            while (iss >> red >> green >> blue) {
//                loadedPixels.push_back({ red, green, blue });
//            }
//        }
//
//        if (loadedPixels.empty()) {
//            std::cout << "文本文件中没有像素数据" << std::endl;
//            return false;
//        }
//
//        width = loadedPixels.size();
//        height = 1;
//        pixels = std::move(loadedPixels);
//
//        return true;
//    }
//
//    //txt转bmp
//    bool saveToFile(const std::string& filename) 
//    {
//        std::ofstream file(filename, std::ios::binary);
//        if (!file) {
//            std::cout << "无法创建输出文件：" << filename << std::endl;
//            return false;
//        }
//
//        file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
//        file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
//
//        int padding = (4 - (width * 3) % 4) % 4;
//        for (int y = height - 1; y >= 0; y--) {
//            for (int x = 0; x < width; x++) {
//                const Pixel& pixel = pixels[y * width + x];
//                uint8_t rgb[3] = { static_cast<uint8_t>(pixel.blue), static_cast<uint8_t>(pixel.green), static_cast<uint8_t>(pixel.red) };
//                file.write(reinterpret_cast<char*>(rgb), sizeof(rgb));
//            }
//            for (int i = 0; i < padding; i++) {
//                file.put(0);
//            }
//        }
//
//        std::cout << "位图已保存为文件：" << filename << std::endl;
//        return true;
//    }
//
//
//private:
//    //drawPixmap(100 + 100 * j, 100 + 100 * i, bmp, 90 * matrix[i][j], 0, 90, 90);
//    int x;
//    int y;
//
//    int spin;
//    int startcut;
//    int w;
//    int h;
//    struct Pixel {
//        int red;
//        int green;
//        int blue;
//    };
//
//    struct BitmapFileHeader {
//        uint16_t type;
//        uint32_t size;
//        uint16_t reserved1;
//        uint16_t reserved2;
//        uint32_t offset;
//    };
//
//    struct BitmapInfoHeader {
//        uint32_t size;
//        int32_t width;
//        int32_t height;
//        uint16_t planes;
//        uint16_t bitCount;
//        uint32_t compression;
//        uint32_t imageSize;
//        int32_t xPixelsPerMeter;
//        int32_t yPixelsPerMeter;
//        uint32_t colorsUsed;
//        uint32_t colorsImportant;
//    };
//
//    BitmapFileHeader fileHeader;
//    BitmapInfoHeader infoHeader;
//    std::vector<Pixel> pixels;
//    int width;
//    int height;
//};


// 抽象存储工厂
class StorageFactory {
public:
    virtual void save_geoshape(const std::vector<GeoShape*>& shapes) = 0;//保存，存到文件txt
    virtual std::vector<GeoShape*> load_geoshape(std::string& filename) = 0;//读文件，设置属性，加载，返回数组（能不能返回paint属性和参数）
    virtual void save_bitmap(Bitmap& bit, const std::string& filename) = 0;
    virtual void load_bitmap(Bitmap& bit, const std::string& filename) = 0;
};

// 文件存储工厂
class FileStorageFactory : public StorageFactory {
public:
    //多个图元放入一个图层
    void save_geoshape(const std::vector<GeoShape*>& shapes) override {
        // 实现文件存储逻辑
        int i;
        std::string a = shapes[i]->merge();//获得相关属性信息
        std::ofstream f0();
        //.......写入到文件

        std::cout << "将图形数据保存到文件" << std::endl;
    }

    void save_bitmap(Bitmap& bit, const std::string& filename);
    void load_bitmap(Bitmap& bit, const std::string& filename);

    std::vector<GeoShape*> load_geoshape(std::string& filename) override {
        // 实现文件加载逻辑
        std::ifstream f0();//加载文件filename ？？
        //........读取文件
        //同时需要判断一个文件里面有多少个图元 搞成string类型 分别将图元设置到shape中 merge（）

        std::cout << "从文件中加载图形数据" << std::endl;
        return std::vector<GeoShape*>();//返回图元列表
    }
};

void FileStorageFactory::save_bitmap(Bitmap& bit,const std::string& filename)
{
    //打开位图bmp 读取信息
    //bool loadFromFile(const std::string & filename) 
    bool flag=false;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "无法打开位图文件：" << filename << std::endl;
        //return false;
        throw 0;
    }

    file.read(reinterpret_cast<char*>(&bit.fileHeader), sizeof(bit.fileHeader));
    file.read(reinterpret_cast<char*>(&bit.infoHeader), sizeof(bit.infoHeader));

    if (bit.fileHeader.type != 0x4D42 || bit.infoHeader.bitCount != 24) {
        std::cout << "不支持的位图格式" << std::endl;
        //return false;
        throw 0;
    }

    int padding = (4 - (bit.infoHeader.width * 3) % 4) % 4;
    bit.pixels.resize(bit.infoHeader.height * bit.infoHeader.width);
    for (int y = bit.infoHeader.height - 1; y >= 0; y--) {
        for (int x = 0; x < bit.infoHeader.width; x++) {
            uint8_t pixel[3];
            file.read(reinterpret_cast<char*>(pixel), sizeof(pixel));
            bit.pixels[y * bit.infoHeader.width + x] = { static_cast<int>(pixel[2]), static_cast<int>(pixel[1]), static_cast<int>(pixel[0]) };
        }
        file.ignore(padding);
    }

    bit.width = bit.infoHeader.width;
    bit.height = bit.infoHeader.height;

    //return true;
    flag = true;

    if (flag)
    {
        std::ofstream file(filename);
        if (!file) {
            std::cout << "无法创建输出文件：" << filename << std::endl;
            //return false;
            throw 0;
        }

        for (int y = bit.height - 1; y >= 0; y--) {
            for (int x = 0; x < bit.width; x++) {
                const Bitmap::Pixel& pixel = bit.pixels[y * bit.width + x];
                file << pixel.red << " " << pixel.green << " " << pixel.blue << " ";
            }
            file << std::endl;
        }

        std::cout << "位图已保存为文本文件：" << filename << std::endl;
        //return true;
    }


    //bool saveAsText(const std::string & filename) {
    //    
    //}
}

void FileStorageFactory::load_bitmap(Bitmap& bit, const std::string& filename)
{
    bool flag = false;
    //打开位图txt
    //bool loadFromText(const std::string & filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "无法打开文本文件：" << filename << std::endl;
        //return false;
        throw 0;
    }

    std::vector<Bitmap::Pixel> loadedPixels;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int red, green, blue;
        while (iss >> red >> green >> blue) {
            loadedPixels.push_back({ red, green, blue });
        }
    }

    if (loadedPixels.empty()) {
        std::cout << "文本文件中没有像素数据" << std::endl;
        //return false;
        throw 0;
    }

    bit.width = loadedPixels.size();
    bit.height = 1;
    bit.pixels = std::move(loadedPixels);

    flag= true;
   /* }*/

    //txt转bmp
   /* bool saveToFile(const std::string & filename)*/
    if(flag)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cout << "无法创建输出文件：" << filename << std::endl;
            /*return false;*/
            throw 0;
        }

        file.write(reinterpret_cast<char*>(&bit.fileHeader), sizeof(bit.fileHeader));
        file.write(reinterpret_cast<char*>(&bit.infoHeader), sizeof(bit.infoHeader));

        int padding = (4 - (bit.width * 3) % 4) % 4;
        for (int y = bit.height - 1; y >= 0; y--) {
            for (int x = 0; x < bit.width; x++) {
                const Bitmap::Pixel& pixel = bit.pixels[y * bit.width + x];
                uint8_t rgb[3] = { static_cast<uint8_t>(pixel.blue), static_cast<uint8_t>(pixel.green), static_cast<uint8_t>(pixel.red) };
                file.write(reinterpret_cast<char*>(rgb), sizeof(rgb));
            }
            for (int i = 0; i < padding; i++) {
                file.put(0);
            }
        }

        std::cout << "位图已保存为文件：" << filename << std::endl;
        /*return true;*/
    }
}


class Bitmap :public Non_GeoShape
{
public:
    Bitmap() : width(0), height(0) {}

    friend void FileStorageFactory::save_bitmap(Bitmap& bit, const std::string& filename);
    friend void FileStorageFactory::load_bitmap(Bitmap& bit, const std::string& filename);

    ////打开位图bmp 读取信息
    //bool loadFromFile(const std::string& filename) {
    //    std::ifstream file(filename, std::ios::binary);
    //    if (!file) {
    //        std::cout << "无法打开位图文件：" << filename << std::endl;
    //        return false;
    //    }

    //    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    //    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    //    if (fileHeader.type != 0x4D42 || infoHeader.bitCount != 24) {
    //        std::cout << "不支持的位图格式" << std::endl;
    //        return false;
    //    }

    //    int padding = (4 - (infoHeader.width * 3) % 4) % 4;
    //    pixels.resize(infoHeader.height * infoHeader.width);
    //    for (int y = infoHeader.height - 1; y >= 0; y--) {
    //        for (int x = 0; x < infoHeader.width; x++) {
    //            uint8_t pixel[3];
    //            file.read(reinterpret_cast<char*>(pixel), sizeof(pixel));
    //            pixels[y * infoHeader.width + x] = { static_cast<int>(pixel[2]), static_cast<int>(pixel[1]), static_cast<int>(pixel[0]) };
    //        }
    //        file.ignore(padding);
    //    }

    //    width = infoHeader.width;
    //    height = infoHeader.height;

    //    return true;
    //}


    //bool saveAsText(const std::string& filename) {
    //    std::ofstream file(filename);
    //    if (!file) {
    //        std::cout << "无法创建输出文件：" << filename << std::endl;
    //        return false;
    //    }

    //    for (int y = height - 1; y >= 0; y--) {
    //        for (int x = 0; x < width; x++) {
    //            const Pixel& pixel = pixels[y * width + x];
    //            file << pixel.red << " " << pixel.green << " " << pixel.blue << " ";
    //        }
    //        file << std::endl;
    //    }

    //    std::cout << "位图已保存为文本文件：" << filename << std::endl;
    //    return true;
    //}

    ////打开位图txt
    //bool loadFromText(const std::string& filename) {
    //    std::ifstream file(filename);
    //    if (!file) {
    //        std::cout << "无法打开文本文件：" << filename << std::endl;
    //        return false;
    //    }

    //    std::vector<Pixel> loadedPixels;
    //    std::string line;
    //    while (std::getline(file, line)) {
    //        std::istringstream iss(line);
    //        int red, green, blue;
    //        while (iss >> red >> green >> blue) {
    //            loadedPixels.push_back({ red, green, blue });
    //        }
    //    }

    //    if (loadedPixels.empty()) {
    //        std::cout << "文本文件中没有像素数据" << std::endl;
    //        return false;
    //    }

    //    width = loadedPixels.size();
    //    height = 1;
    //    pixels = std::move(loadedPixels);

    //    return true;
    //}

    ////txt转bmp
    //bool saveToFile(const std::string& filename)
    //{
    //    std::ofstream file(filename, std::ios::binary);
    //    if (!file) {
    //        std::cout << "无法创建输出文件：" << filename << std::endl;
    //        return false;
    //    }

    //    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    //    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    //    int padding = (4 - (width * 3) % 4) % 4;
    //    for (int y = height - 1; y >= 0; y--) {
    //        for (int x = 0; x < width; x++) {
    //            const Pixel& pixel = pixels[y * width + x];
    //            uint8_t rgb[3] = { static_cast<uint8_t>(pixel.blue), static_cast<uint8_t>(pixel.green), static_cast<uint8_t>(pixel.red) };
    //            file.write(reinterpret_cast<char*>(rgb), sizeof(rgb));
    //        }
    //        for (int i = 0; i < padding; i++) {
    //            file.put(0);
    //        }
    //    }

    //    std::cout << "位图已保存为文件：" << filename << std::endl;
    //    return true;
    //}


private:
    //drawPixmap(100 + 100 * j, 100 + 100 * i, bmp, 90 * matrix[i][j], 0, 90, 90);
    int x;
    int y;

    int spin;
    int startcut;
    int w;
    int h;
    struct Pixel {
        int red;
        int green;
        int blue;
    };

    struct BitmapFileHeader {
        uint16_t type;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    };

    struct BitmapInfoHeader {
        uint32_t size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bitCount;
        uint32_t compression;
        uint32_t imageSize;
        int32_t xPixelsPerMeter;
        int32_t yPixelsPerMeter;
        uint32_t colorsUsed;
        uint32_t colorsImportant;
    };

    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    std::vector<Pixel> pixels;
    int width;
    int height;
};


// 数据库存储工厂
class DatabaseStorageFactory : public StorageFactory {
public:
    void save_geoshape(const std::vector<GeoShape*>& shapes) override
    {
        // 实现数据库存储逻辑
        std::cout << "将图形数据保存到数据库" << std::endl;
    }

    std::vector<GeoShape*> load_geoshape() override
    {
        // 实现数据库加载逻辑
        std::cout << "从数据库中加载图形数据" << std::endl;
        return std::vector<GeoShape*>();
    }
};

// 图形管理类
class GraphicsManager {
private:
    std::vector<GeoShape*> shapes; // 存储图元的容器
    StorageFactory* storageFactory; // 存储工厂

public:
    GraphicsManager(StorageFactory* factory) : storageFactory(factory) {}

    void addShape(GeoShape* shape) {
        shapes.push_back(shape);
    }

    void saveShapes() {
        storageFactory->save_geoshape(shapes);
    }

    void loadShapes() {
        shapes = storageFactory->load_geoshape();
    }

    //传给2，返回两个参数，包括画笔属性以及参数属性
    std::vector<int> getShapes() {
        std::vector<int> a;
        for (GeoShape* shape : shapes) {
            //shape->draw();
        }
        return a;
    }
};