#include "../shaderClass.h"

std::string get_file_contents(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if(in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    //create vertex shader object and get reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader source to th vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile vertex shader into machine code
	glCompileShader(vertexShader);

	//create fragment shader object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile the fragment shader into machine code
	glCompileShader(fragmentShader);

	//create shader program object and its reference
	ID = glCreateProgram();
	//attach shaders to program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//link shaders in shader program
	glLinkProgram(ID);

	//delete the now useless shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    //tell opengl what program we want to use
	glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}