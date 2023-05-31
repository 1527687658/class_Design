#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>




class GeoShape 
{
public:
    virtual std::string merge() = 0;//�������ԣ�������д���ļ�
    virtual void read_picture() = 0;//���ѻ��Ƶ�ͼԪ���õ�����
    virtual void read_file(std::vector<int>) = 0;//���ļ�������������
    virtual void getcolor()=0;//��û������
    virtual void getproperty()=0;//������ò���
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
    int size;//��Ĵ�С
};

class line :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;
    int size;//�߿�
};

class polygon :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;
};

//drawRect(20,20,160,160); (���Ͻ����xy,��,��)
class rectangle :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;//���Ͻ����xy
    int width;
    int height;
};
//drawEllipse(20,20,210,160);�������Ͻǣ�����
class circle :public GeoShape
{
public:
private:
    int color[4];
    int type;
    std::vector<int> m_pos;//�������Ͻǵĵ�
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
    Point pos;//���õ�����λ��
};

class txt :public Non_GeoShape
{
public:

private:

    //p.setFont(QFont("΢���ź�", 15, 700, false));
    std::string style;//����
    int size;//�����С
    int blod;//����Ȩ��
    bool italic;//�Ƿ�б��

    //drawText(QPoint(20, 60), "����:" + QString::number(score));
    Point pos;//����λ��
    std::string content;//����
};


class Bitmap/* :public Non_GeoShape*/;
//{
//public:
//    Bitmap() : width(0), height(0) {}
//
//    friend void FileStorageFactory::save_bitmap(Bitmap& bit, const std::string& filename);
//
//    //��λͼbmp ��ȡ��Ϣ
//    bool loadFromFile(const std::string& filename) {
//        std::ifstream file(filename, std::ios::binary);
//        if (!file) {
//            std::cout << "�޷���λͼ�ļ���" << filename << std::endl;
//            return false;
//        }
//
//        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
//        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
//
//        if (fileHeader.type != 0x4D42 || infoHeader.bitCount != 24) {
//            std::cout << "��֧�ֵ�λͼ��ʽ" << std::endl;
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
//            std::cout << "�޷���������ļ���" << filename << std::endl;
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
//        std::cout << "λͼ�ѱ���Ϊ�ı��ļ���" << filename << std::endl;
//        return true;
//    }
//
//    //��λͼtxt
//    bool loadFromText(const std::string& filename) {
//        std::ifstream file(filename);
//        if (!file) {
//            std::cout << "�޷����ı��ļ���" << filename << std::endl;
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
//            std::cout << "�ı��ļ���û����������" << std::endl;
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
//    //txtתbmp
//    bool saveToFile(const std::string& filename) 
//    {
//        std::ofstream file(filename, std::ios::binary);
//        if (!file) {
//            std::cout << "�޷���������ļ���" << filename << std::endl;
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
//        std::cout << "λͼ�ѱ���Ϊ�ļ���" << filename << std::endl;
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


// ����洢����
class StorageFactory {
public:
    virtual void save_geoshape(const std::vector<GeoShape*>& shapes) = 0;//���棬�浽�ļ�txt
    virtual std::vector<GeoShape*> load_geoshape(std::string& filename) = 0;//���ļ����������ԣ����أ��������飨�ܲ��ܷ���paint���ԺͲ�����
    virtual void save_bitmap(Bitmap& bit, const std::string& filename) = 0;
    virtual void load_bitmap(Bitmap& bit, const std::string& filename) = 0;
};

// �ļ��洢����
class FileStorageFactory : public StorageFactory {
public:
    //���ͼԪ����һ��ͼ��
    void save_geoshape(const std::vector<GeoShape*>& shapes) override {
        // ʵ���ļ��洢�߼�
        int i;
        std::string a = shapes[i]->merge();//������������Ϣ
        std::ofstream f0();
        //.......д�뵽�ļ�

        std::cout << "��ͼ�����ݱ��浽�ļ�" << std::endl;
    }

    void save_bitmap(Bitmap& bit, const std::string& filename);
    void load_bitmap(Bitmap& bit, const std::string& filename);

    std::vector<GeoShape*> load_geoshape(std::string& filename) override {
        // ʵ���ļ������߼�
        std::ifstream f0();//�����ļ�filename ����
        //........��ȡ�ļ�
        //ͬʱ��Ҫ�ж�һ���ļ������ж��ٸ�ͼԪ ���string���� �ֱ�ͼԪ���õ�shape�� merge����

        std::cout << "���ļ��м���ͼ������" << std::endl;
        return std::vector<GeoShape*>();//����ͼԪ�б�
    }
};

void FileStorageFactory::save_bitmap(Bitmap& bit,const std::string& filename)
{
    //��λͼbmp ��ȡ��Ϣ
    //bool loadFromFile(const std::string & filename) 
    bool flag=false;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "�޷���λͼ�ļ���" << filename << std::endl;
        //return false;
        throw 0;
    }

    file.read(reinterpret_cast<char*>(&bit.fileHeader), sizeof(bit.fileHeader));
    file.read(reinterpret_cast<char*>(&bit.infoHeader), sizeof(bit.infoHeader));

    if (bit.fileHeader.type != 0x4D42 || bit.infoHeader.bitCount != 24) {
        std::cout << "��֧�ֵ�λͼ��ʽ" << std::endl;
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
            std::cout << "�޷���������ļ���" << filename << std::endl;
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

        std::cout << "λͼ�ѱ���Ϊ�ı��ļ���" << filename << std::endl;
        //return true;
    }


    //bool saveAsText(const std::string & filename) {
    //    
    //}
}

void FileStorageFactory::load_bitmap(Bitmap& bit, const std::string& filename)
{
    bool flag = false;
    //��λͼtxt
    //bool loadFromText(const std::string & filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "�޷����ı��ļ���" << filename << std::endl;
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
        std::cout << "�ı��ļ���û����������" << std::endl;
        //return false;
        throw 0;
    }

    bit.width = loadedPixels.size();
    bit.height = 1;
    bit.pixels = std::move(loadedPixels);

    flag= true;
   /* }*/

    //txtתbmp
   /* bool saveToFile(const std::string & filename)*/
    if(flag)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cout << "�޷���������ļ���" << filename << std::endl;
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

        std::cout << "λͼ�ѱ���Ϊ�ļ���" << filename << std::endl;
        /*return true;*/
    }
}


class Bitmap :public Non_GeoShape
{
public:
    Bitmap() : width(0), height(0) {}

    friend void FileStorageFactory::save_bitmap(Bitmap& bit, const std::string& filename);
    friend void FileStorageFactory::load_bitmap(Bitmap& bit, const std::string& filename);

    ////��λͼbmp ��ȡ��Ϣ
    //bool loadFromFile(const std::string& filename) {
    //    std::ifstream file(filename, std::ios::binary);
    //    if (!file) {
    //        std::cout << "�޷���λͼ�ļ���" << filename << std::endl;
    //        return false;
    //    }

    //    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    //    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    //    if (fileHeader.type != 0x4D42 || infoHeader.bitCount != 24) {
    //        std::cout << "��֧�ֵ�λͼ��ʽ" << std::endl;
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
    //        std::cout << "�޷���������ļ���" << filename << std::endl;
    //        return false;
    //    }

    //    for (int y = height - 1; y >= 0; y--) {
    //        for (int x = 0; x < width; x++) {
    //            const Pixel& pixel = pixels[y * width + x];
    //            file << pixel.red << " " << pixel.green << " " << pixel.blue << " ";
    //        }
    //        file << std::endl;
    //    }

    //    std::cout << "λͼ�ѱ���Ϊ�ı��ļ���" << filename << std::endl;
    //    return true;
    //}

    ////��λͼtxt
    //bool loadFromText(const std::string& filename) {
    //    std::ifstream file(filename);
    //    if (!file) {
    //        std::cout << "�޷����ı��ļ���" << filename << std::endl;
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
    //        std::cout << "�ı��ļ���û����������" << std::endl;
    //        return false;
    //    }

    //    width = loadedPixels.size();
    //    height = 1;
    //    pixels = std::move(loadedPixels);

    //    return true;
    //}

    ////txtתbmp
    //bool saveToFile(const std::string& filename)
    //{
    //    std::ofstream file(filename, std::ios::binary);
    //    if (!file) {
    //        std::cout << "�޷���������ļ���" << filename << std::endl;
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

    //    std::cout << "λͼ�ѱ���Ϊ�ļ���" << filename << std::endl;
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


// ���ݿ�洢����
class DatabaseStorageFactory : public StorageFactory {
public:
    void save_geoshape(const std::vector<GeoShape*>& shapes) override
    {
        // ʵ�����ݿ�洢�߼�
        std::cout << "��ͼ�����ݱ��浽���ݿ�" << std::endl;
    }

    std::vector<GeoShape*> load_geoshape() override
    {
        // ʵ�����ݿ�����߼�
        std::cout << "�����ݿ��м���ͼ������" << std::endl;
        return std::vector<GeoShape*>();
    }
};

// ͼ�ι�����
class GraphicsManager {
private:
    std::vector<GeoShape*> shapes; // �洢ͼԪ������
    StorageFactory* storageFactory; // �洢����

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

    //����2�����������������������������Լ���������
    std::vector<int> getShapes() {
        std::vector<int> a;
        for (GeoShape* shape : shapes) {
            //shape->draw();
        }
        return a;
    }
};