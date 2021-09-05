#include "Shader.h"

namespace Umbra2D {

void Shader::bind() {
    glUseProgram(id);
}
void Shader::unbind() {
    glUseProgram(0);
}
unsigned int Shader::getUniformID(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}
void Shader::setMat4(const std::string& name, const glm::mat4* mat, size_t how_many) {
    bind();
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), (GLsizei)how_many, GL_FALSE, (const GLfloat*)mat);
}
void Shader::setVec2(const std::string& name, const glm::vec2 value) {
    bind();
    glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}
void Shader::setVec3(const std::string& name, const glm::vec3 vec) {
    bind();
    glUniform3f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z);
}
void Shader::setVec4(const std::string& name, glm::vec4 vec) {
    bind();
    glUniform4f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z, vec.a);
}
void Shader::setBool(const std::string& name, bool value) {
    bind();
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setInt(const std::string& name, int value) {
    bind();
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, const float value) {
    bind();
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setTexture(const std::string& name, int value, int textureUnit) {
    this->setInt(name, textureUnit);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, value);
}

Shader::Shader(std::string filepath_v, std::string filepath_f, std::string filepath_g) {
    //std::cout << "Reading " << filepath_f << " " << filepath_v << "\n";
    ShaderProgramSource source = ParseShader(filepath_v, filepath_f, filepath_g);
    this->id = CreateShader(source.vertexShader, source.fragmentShader, source.geometryShader);
    free(source.fragmentShader);
    free(source.vertexShader);
    if (source.geometryShader) 
        free(source.geometryShader);
}
Shader::~Shader() {
    glDeleteProgram(id);
}

void readShader(std::string path, char** writeHere) {
    *writeHere = (char*)calloc(9999999, sizeof(char));
    
    std::ifstream f;
    f.open(path.c_str());
    std::string line;

    if(f.is_open()) {
        while (std::getline(f, line)) {
            strcat(*writeHere, line.c_str());
            strcat(*writeHere, "\n");
        }
        f.close();
        (*writeHere)[strlen(*writeHere) - 1] = '\0';
    }
}

ShaderProgramSource Shader::ParseShader(std::string filepath_v, std::string filepath_f, std::string filepath_g)
{
    ShaderProgramSource source{};
    readShader(filepath_v, &source.vertexShader);
    readShader(filepath_f, &source.fragmentShader);
    if (filepath_g.size() != 0) {
        readShader(filepath_g, &source.geometryShader);
    }
    
    return source;
}

unsigned int Shader::CreateShader(const char* vertexShader, const char* fragmentShader, const char* geometryShader = nullptr) {
    unsigned int program = glCreateProgram();
    
    unsigned int vs, fs, gs;

    vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    glAttachShader(program, vs);

    if (geometryShader) {
        gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
        glAttachShader(program, gs);
    }
    
    fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, fs);
    
    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        std::cout << "Perhaps the relative path to the shader is wrong\n";
        int infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar buffer[8888];
        GLsizei charsWritten = 0;
        glGetProgramInfoLog(program, infoLogLength, &charsWritten, buffer);
        std::cout << buffer << std::endl;
    }

    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    if (geometryShader)
        glDeleteShader(gs);
    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const char* source) {
    unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    int result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderID, length, &length, message);
        std::cout << message << std::endl;
    }

    return shaderID;
}

}