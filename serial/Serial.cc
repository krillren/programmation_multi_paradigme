#include "Serial.h"
#include "stdexcept"


namespace serial {
    /*
        OBinaryFile class
    */
    OBinaryFile::OBinaryFile(const std::string& filename, Mode mode)
    {
        auto m = ((mode == Mode::Truncate)? "w" : "a");
        m_file = fopen(filename.c_str(),m);
        if(m_file == nullptr){
            throw std::runtime_error(filename + " : fichier introuvable");
        }
    }

    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept{
        m_file = other.m_file;
        other.m_file = nullptr;
    }

    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept{
        m_file = other.m_file;
        other.m_file = nullptr;
        return *this;
    }

    OBinaryFile::~OBinaryFile(){
        if(m_file != nullptr){
            fclose(m_file);
        }
    }
    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size){
        std::size_t written = fwrite(data,sizeof(std::byte), size,m_file);
        return written;
    }




    /*
        IBinaryFile class
    */
    IBinaryFile::IBinaryFile(const std::string& filename){
        m_file = fopen(filename.c_str(),"r");
        if(m_file == nullptr){
            throw std::runtime_error(filename + " : fichier introuvable");
        }
    }

    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept{
        m_file = other.m_file;
        other.m_file = nullptr;
    }

    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept{
        m_file = other.m_file;
        other.m_file = nullptr;
        return *this;
    }

    IBinaryFile::~IBinaryFile(){
        if(m_file != nullptr){
            fclose(m_file);
        }
    }

    std::size_t IBinaryFile::read(std::byte* data, std::size_t size){
        std::size_t read = fread(data, size,sizeof(std::byte),m_file);
        return read;
    }


    /*
        Operators
    */

    OBinaryFile &operator<<(OBinaryFile &file, uint8_t x) {

        file.write(reinterpret_cast<std::byte *>(&x), sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int8_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, uint16_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int16_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, uint32_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int32_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, uint64_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int64_t x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, char x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, float x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, double x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, bool x) {
        file.write(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, const std::string &x) {
        file<<x.size();
        file.write(reinterpret_cast<const std::byte*>(x.data()),x.size());
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int8_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint8_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int16_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint16_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int32_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint32_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int64_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint64_t &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, char &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, float &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, double &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, bool &x) {
        file.read(reinterpret_cast<std::byte*>(&x),sizeof(x));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, std::string &x) {
        size_t size;
        file>>size;
        if(size <= 0){x.clear();return file;}
        x.resize(size);
        char data[size];
        file.read(reinterpret_cast<std::byte*>(data),size);
        x.assign(data,size);
        return file;
    }

}
