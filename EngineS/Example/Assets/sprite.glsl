#ifdef VERTEX

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}

#endif

#ifdef FRAGMENT

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}

#endif