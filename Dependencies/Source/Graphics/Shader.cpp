#include "Umbra2D.h"

namespace Umbra2D::Graphics {

void Shader::bind() {
    glUseProgram(id);
}
void Shader::unbind() {
    glUseProgram(0);
}
std::string Shader::getName() {
    return name;
}
std::pair<std::string, std::string> Shader::getPaths() {
    return {pathv, pathf};
}
unsigned int Shader::getUniformID(const std::string& uniformName) {
    return glGetUniformLocation(id, uniformName.c_str());
}
void Shader::setMat4(const std::string& uniformName, const glm::mat4* mat, size_t how_many) {
    bind();
    glUniformMatrix4fv(glGetUniformLocation(id, uniformName.c_str()), (GLsizei)how_many, GL_FALSE, (const GLfloat*)mat);
}
void Shader::setMat4(const std::string& uniformName, const glm::mat4 mat) {
    setMat4(uniformName, &mat, 1);
}
void Shader::setVec2(const std::string& uniformName, const glm::vec2 value) {
    bind();
    glUniform2f(glGetUniformLocation(id, uniformName.c_str()), value.x, value.y);
}
void Shader::setVec3(const std::string& uniformName, const glm::vec3 vec) {
    bind();
    glUniform3f(glGetUniformLocation(id, uniformName.c_str()), vec.x, vec.y, vec.z);
}
void Shader::setVec4(const std::string& uniformName, glm::vec4 vec) {
    bind();
    glUniform4f(glGetUniformLocation(id, uniformName.c_str()), vec.x, vec.y, vec.z, vec.a);
}
void Shader::setBool(const std::string& uniformName, bool value) {
    bind();
    glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
}
void Shader::setInt(const std::string& uniformName, int value) {
    bind();
    glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
}
void Shader::setFloat(const std::string& uniformName, const float value) {
    bind();
    glUniform1f(glGetUniformLocation(id, uniformName.c_str()), value);
}
void Shader::setTexture(const std::string& uniformName, int value, int textureUnit) {
    this->setInt(uniformName, textureUnit);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, value);
}

void Shader::gui() {
    if (ImGui::TreeNode("Shader")) {
        ImGui::Text(name.c_str());
        ImGui::Text(pathv.c_str());
        ImGui::Text(pathf.c_str());
        ImGui::TreePop();
    }
}



Shader::Shader() {

}
Shader::~Shader() {
    glDeleteProgram(id);
}

Shader* Shader::loadShader(std::string shaderName, std::string filepath_v, std::string filepath_f, std::string filepath_g) {
    this->name = shaderName; this->pathv = filepath_v; this->pathf = filepath_f;
    ShaderProgramSource source = ParseShader(filepath_v, filepath_f, filepath_g);
    this->id = CreateShader(source.vertexShader, source.fragmentShader, source.geometryShader);
    free(source.fragmentShader);
    free(source.vertexShader);
    if (source.geometryShader)
        free(source.geometryShader);
    return this;
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
    
    unsigned int vs{}, fs{}, gs{};

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
