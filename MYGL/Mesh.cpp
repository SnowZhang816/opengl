#include "Mesh.h"
#include <string>
#include "Model.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Model *model)
{
    this->model = model;
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCords));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shader = new Shader("assets/shader/meshshader.vsh", "assets/shader/meshshader.fsh");
}

Mesh::~Mesh()
{
}

void Mesh::draw(Camera* ca, const std::vector<Light>& lights, Light& spotlight)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->model->getPosition());

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", ca->getViewMatrix());
    shader->setMat4("projection", ca->getProjectionMatrix());
    shader->setFloat("intensity", 0.2);
    shader->setVec3("viewPos", ca->getPosition());
    // shader->setVec3("material.ambient", glm::vec3(0.0f, 0.1f, 0.06f));
    // shader->setVec3("material.diffuse", glm::vec3(0.0f, 0.50980392f, 0.50980392f));
    // shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setFloat("material.shininess", 10.0f);

    //平行光
    shader->setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader->setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    shader->setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
    shader->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f)); 

    //点光源
    shader->setInt("pointLightNum", lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        Light light = lights.at(i);
        char buff[100];
        sprintf_s(buff, "pointLights[%d].position", i);
        shader->setVec3(buff, light.getPosition());
        sprintf_s(buff, "pointLights[%d].ambient", i);
        shader->setVec3(buff, light.getColor() * glm::vec3(0.2));
        sprintf_s(buff, "pointLights[%d].diffuse", i);
        shader->setVec3(buff, light.getColor() * glm::vec3(0.5f)); // darken diffuse light a bit
        sprintf_s(buff, "pointLights[%d].specular", i);
        shader->setVec3(buff, glm::vec3(1.0f, 1.0f, 1.0f)); 
        sprintf_s(buff, "pointLights[%d].constant", i);
        shader->setFloat(buff,  1.0f);
        sprintf_s(buff, "pointLights[%d].linear", i);
        shader->setFloat(buff, 0.014f);
        sprintf_s(buff, "pointLights[%d].quadratic", i);
        shader->setFloat(buff, 0.0007f);
    }

    //聚光灯
    shader->setVec3("spotLight.direction", spotlight.getDirection());
    shader->setVec3("spotLight.position", spotlight.getPosition());
    shader->setVec3("spotLight.ambient", spotlight.getColor() * glm::vec3(0.1));
    shader->setVec3("spotLight.diffuse", spotlight.getColor() * glm::vec3(0.5f)); // darken diffuse light a bit
    shader->setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
    shader->setFloat("spotLight.cutOff", spotlight.getCutOff()); 
    shader->setFloat("spotLight.outerCutOff", spotlight.getOuterCutOff()); 
    shader->setFloat("spotLight.constant", 1.0f); 
    shader->setFloat("spotLight.linear", 0.014f); 
    shader->setFloat("spotLight.quadratic", 0.0007f); 

    unsigned int diffNum = 1;
    unsigned int specNum = 1;
    unsigned int normalNum   = 1;
    unsigned int heightNum   = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        Texture texture = textures[i];
        std::string number;
        std::string name = texture.name;
        if(name == "texture_diffuse") 
        {
            number = std::to_string(diffNum++);
        }
        else if(name == "texture_specular")
        {
            number = std::to_string(specNum++);
        }
        else if(name == "texture_normal")
        {
            number = std::to_string(normalNum++);
        }
        else if(name == "texture_height")
        {
            number = std::to_string(heightNum++);
        }
        
        std::string ns = ("material." + name + number).c_str();
        shader->setInt(ns, i);
        texture.use(GL_TEXTURE0 + i);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
