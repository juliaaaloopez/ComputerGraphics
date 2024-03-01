// Global variables from the CPU to send to the GPU
uniform mat4 u_model;
uniform mat4 u_viewprojection;
uniform vec3 u_camera_position;

uniform vec3 u_Ka;
uniform vec3 u_Ks;
uniform vec3 u_Kd;
uniform float u_a;

uniform vec2 u_lightPosition;
uniform vec3 u_diffuseIntensity;
uniform vec3 u_specularIntensity;
uniform vec3 u_ambientLight;


// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 frag_color;

//here create uniforms for all the data we need here

void main() //code for projecting vertices of mesh
{
	v_uv = gl_MultiTexCoord0.xy;

	// Convert local position to world space
	vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;

	// Convert local normal to world space
	vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz;
    
    // Pass them to the fragment shader interpolated
    v_world_position = world_position;
    v_world_normal = world_normal;
    
    //diffuse reflection --> Kd*(Lm dot N)*Im,d
    vec3 L = normalize(vec3(u_lightPosition, 1.0)- world_position.xyz); //distance from vertex to light source
    float diffuse = clamp(dot(world_normal, L), 0.0, 1.0); //we clamp the dot product between 0 and 1
    vec3 diffuse_reflection = u_Kd * diffuse * u_diffuseIntensity;
    
    //specular reflection --> Ks*(Rm dot V)^a*Im,s
    vec3 R = reflect(-L, world_normal);
    vec3 V = normalize(u_camera_position - world_position.xyz);
    float specular = pow(clamp(dot(R, V), 0.0, 1.0), u_a);
    vec3 specular_reflection = u_Ks * specular * u_specularIntensity;
    
    //ambient reflection --> Ka*Ia
    vec3 ambient_reflection = u_Ka * u_ambientLight;
	
	// ambient relfection + dist(diffuse relection + specular reflection)
    float dist_ = 1.0/pow(distance(world_position, vec3(u_lightPosition, 1.0)), 2.0);
    frag_color = ambient_reflection + dist_ *(diffuse_reflection + specular_reflection);

	// Project the vertex using the model view projection matrix
    // we are passing the vertices from world space to clip space
	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader
}
