#pragma once

#include <Common.h>

/*
 *  Shader class used for:
 *  - reading shaders from file
 *  - compiling the code
 *  - sending different types of data structures to the vertex/geometry/fragment shader
 */


struct ShaderProgramSource
{
    char* vertexShader;
    char* fragmentShader;
    char* geometryShader;
};


namespace Umbra2D::Graphics {
class Shader
{
	unsigned int id;
    std::string name, pathv, pathf;
public:

    void bind();
    void unbind();

    std::string getName();
    std::pair<std::string, std::string> getPaths();

    unsigned int getUniformID(const std::string& name);
    void setMat4(const std::string& name, const glm::mat4* mat, size_t how_many = 1);
    void setMat4(const std::string& name, const glm::mat4 mat);
    void setVec4(const std::string& name, glm::vec4 vec);
    void setVec2(const std::string& name, const glm::vec2 value);
    void setVec3(const std::string& name, const glm::vec3 vec);
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, const float value);

    void setTexture(const std::string& name, int value, int textureUnit);
    void gui();

    Shader();
    ~Shader();

    Shader* loadShader(std::string name, std::string filepath_v, std::string filepath_f, std::string filepath_g = "");

private:
    // reads the shaders from the files and returns a ShaderProgramSource struct
    static ShaderProgramSource ParseShader(std::string filepath_v, std::string filepath_f, std::string filepath_g);
    
    /* compiles the shader
     *  - type: GL_VERTEX_SHADER/GL_FRAGMENT_SHADER/GL_GEOMETRY_SHADER
     *  - source: char array containing the source code of the shader
     */
    unsigned int CompileShader(unsigned int type, const char* source);
    //* Links the shaders together and returns the internal id of the group
    unsigned int CreateShader(const char* vertexShader, const char* fragmentShader, const char* geometryShader);

};

}
