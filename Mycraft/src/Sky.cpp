//
//  Sky.cpp
//  Mycraft
//
//  Created by Clapeysron on 08/12/2017.
//  Copyright © 2017 Clapeysron. All rights reserved.
//

#include "Sky.hpp"
#include <vector>
#include "Stbi_load.hpp"

float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    
    
    0.0f, 1.0f, 0.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    
    0.0f, 1.0f, 0.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    
    0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    0.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    
    0.0f, -1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    
    0.0f, -1.0f, 0.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    
    0.0f, -1.0f, 0.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f
};

void Sky::Sky_init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glGenTextures(1, &Skybox_pic);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Skybox_pic);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load_out("picture/skybox.png", &width, &height, &nrChannels, STBI_rgb_alpha_out);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        std::cout << "Cubemap texture failed to load at path: " << "picture/skybox.png" << std::endl;
    }
    stbi_image_free_out(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    Star_init();
}

void Sky::Star_init() {
    std::vector<std::string> faces {
        "picture/skybox/right.png",
        "picture/skybox/left.png",
        "picture/skybox/top.png",
        "picture/skybox/bottom.png",
        "picture/skybox/back.png",
        "picture/skybox/front.png"
    };
    glGenTextures(1, &Star_pic);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Star_pic);
    
    int width, height, nrChannels;
    for (int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load_out(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
        stbi_image_free_out(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Sky::~Sky() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Sky::draw(glm::vec3 position, glm::mat4 view, glm::mat4 projection, float dayTime, float starIntensity) {
    glDepthFunc(GL_LEQUAL);
    Sky_Shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Skybox_pic);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Star_pic);
    view = glm::mat4(glm::mat3(view));
    Sky_Shader.setMat4("view", view);
    Sky_Shader.setMat4("projection", projection);
    Sky_Shader.setFloat("starIntensity", starIntensity);
    float dayPos = dayTime/24;
    Sky_Shader.setFloat("DayPos", dayPos);
    Sky_Shader.setInt("skybox", 0);
    Sky_Shader.setInt("star", 1);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 48);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
