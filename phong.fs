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

// Variables passed from the vertex shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;

// pass our texture in uniform type (Image)
uniform sampler2D u_texture_normal;
uniform sampler2D u_texture_color;
uniform vec3 u_texture_flag;

void main()
{
	// Set the ouput color per pixel
    
   
    if(u_texture_flag.r == 1.0){
        vec4 texture_color = texture2D(u_texture_color, v_uv);
        vec3 diffuse_color = texture_color.rgb;
    }
    
    if(u_texture_flag.g == 1.0){
        vec4 texture_normal = texture2D(u_texture_normal, v_uv);
        vec3 diffuse_color = texture_normal.rgb;
    }
    
    if(u_texture_flag.b == 1.0){
        vec4 texture_normal = texture2D(u_texture_normal, v_uv);
        vec3 diffuse_color = texture_normal.rgb;
        vec3 normal_map = normalize(texture_normal * 2.0 - 1.0);
        float mix_factor = 0.5;
        vec3 final_normal = mix(v_world_normal, normal_map, mix_factor);
    }
    
    //diffuse reflection
    vec3 L = normalize(vec3(u_lightPosition, 1.0) - v_world_position.xyz); //distance from vertex to light source
    float diffuse = clamp(dot(final_normal, L), 0.0, 1.0); //we clamp the dot product between 0 and 1
    vec3 diffuse_reflection = diffuse_color * diffuse * u_diffuseIntensity;
    
    //specular reflection --> Ks*(Rm dot V)^a*Im,s
    vec3 R = reflect(-L, final_normal);
    vec3 V = normalize(u_camera_position - v_world_position.xyz);
    float specular = pow(clamp(dot(R, V), 0.0, 1.0), u_a);
    vec3 specular_reflection = texture_color.a * specular * u_specularIntensity;
    
    //ambient reflection --> Ka*Ia
    vec3 ambient_reflection = u_Ka * diffuse_color * u_ambientLight;
    
    // ambient relfection + dist(diffuse relection + specular reflection)
    float dist_ = 1.0/pow(distance(v_world_position, vec3(u_lightPosition, 1.0)), 2.0);
    vec3 frag_color = ambient_reflection + dist_*(specular_reflection + diffuse_reflection);

	gl_FragColor = vec4(frag_color, texture_color.a);
}
