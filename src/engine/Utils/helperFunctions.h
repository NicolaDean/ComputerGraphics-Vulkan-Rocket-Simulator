
#include <fstream>
#include "../commonLibs.h"
namespace Engine{

    /**
     * Simply Load File with name "filename"
     * @param filename  name of file to open
     * @return
     */
    static std::vector<char> readFile(const std::string& filename) {

        /**
         * READ FILE:
         *      -ate: read file from bottom (EOF) -> this allow to determine file size to allocate buffer
         *      -binary: dosn't convert to ASCII but simply read binary format
         */
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        //Check if file is being opened
        if (!file.is_open()) {
            //printf("Error opening file:\t %s",filename);
            throw std::runtime_error("failed to open file!");
        }

        //Allocate Buffer
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        //Go back at start of file
        file.seekg(0);
        file.read(buffer.data(), fileSize);

        //Close file
        file.close();

        return buffer;
    }

}