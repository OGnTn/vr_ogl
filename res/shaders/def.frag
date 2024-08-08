#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

in vec3 Normal;
in vec3 fragPos;

uniform sampler2D texture0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{

   float ambient = 0.2f;


   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(lightPos - fragPos);

   float diffuse = max(dot(normal, lightDir), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDir = normalize(camPos - fragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 8);
   float specular = specularLight * specAmount;

   FragColor = texture(texture0, texCoord) * (diffuse + ambient + specular) * lightColor;
}