#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

in vec3 Normal;
in vec3 fragPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 point_light() {

   vec3 light_vector = lightPos - fragPos;
   float light_distance = length(light_vector);

   float quadratic = 0.1f;
   float linear = 0.3f;
   float constant = 1.0f;
   float intensity = 1.0f / (quadratic * pow(light_distance, 2) + linear * light_distance + constant);

   float ambient = 0.2f;
   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(light_vector);

   float diffuse = max(dot(normal, lightDir), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDir = normalize(camPos - fragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
   float specular = specularLight * specAmount;

   return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
   }

vec4 spot_light() {

   float outer_cone = 0.90f;
   float inner_cone = 0.95f;

   vec3 light_vector = lightPos - fragPos;

   float ambient = 0.2f;
   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(light_vector);

   float diffuse = max(dot(normal, lightDir), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDir = normalize(camPos - fragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
   float specular = specularLight * specAmount;

   float theta = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
   float intensity = clamp((theta - outer_cone) / (inner_cone - outer_cone), 0.0f, 1.0f);

   return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
   }

vec4 directional_light() {


   float ambient = 0.2f;
   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));

   float diffuse = max(dot(normal, lightDir), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDir = normalize(camPos - fragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
   float specular = specularLight * specAmount;

   return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
   }

void main()
{
	FragColor = spot_light();
}