varying vec2 v_uv;
//we can use time but we can use also an integer
uniform float u_time;
uniform sampler2D u_texture;
uniform float u_subtask;

void main()
{
   
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    if(u_subtask == 1.0){
        //fragment shader
        //argv alpha value vector 4
        gl_FragColor = vec4(v_uv.x, 0.0, 1.0-v_uv.x, 0.0); //everything RED if first component is 1.0
        //if we put v_uv.x we will have a horizontal gradient
        //with sinus we change the instensity of one of the colors
        //we overlap the two colors by adding 1.0-v_uv.x
    }
    if(u_subtask == 2.0){
        vec2 center = vec2(0.5); //we will define our center (of rectangle)
        float dist_ = distance(center, v_uv);
        vec3 final_color = vec3(dist_);
        gl_FragColor = vec4(final_color, 0.0);
    }
    
    
    if(u_subtask == 3.0){
        float blur = 0.15;
        float red = smoothstep(0.4 - blur, 0.4, fract(v_uv.x * 5.0)) - smoothstep(0.6, 0.6 + blur, fract(v_uv.x * 5.0));
        float blue = smoothstep(0.4 - blur, 0.4, fract(v_uv.y * 5.0)) - smoothstep(0.6, 0.6 + blur, fract(v_uv.y * 5.0));
        gl_FragColor = vec4(red, 0.0, blue, 1.0);
    }
    
    if(u_subtask == 4.0){
        float rows = floor(v_uv.x * 20.0)/20.0;
        float cols = floor(v_uv.y * 20.0)/20.0;
        gl_FragColor = vec4(rows, cols, 0.0, 0.0);
    }
    
    
    if(u_subtask == 5.0){
        vec2 uv = v_uv * 16.0; // number of squares. In this case we want 16 x 16 squares.
        float black = step(0.5, mod(floor(uv.x) + floor(uv.y), 2.0)); //we use the step function to calculate whether the square is black or white.
        gl_FragColor = vec4(vec3(1.0 - black), 1.0);
    }
    
    if(u_subtask == 6.0){
        vec2 center = vec2(0.5, 0.5);
        float wave = -sin((v_uv.x - center.x) * 6.0) * 0.3 + center.y;
        float silhouette = smoothstep(wave, wave, v_uv.y);
        float gradientFactor = smoothstep(0.0, 0.5, center.y - v_uv.y);
        vec4 finalColor = mix(mix(vec4(0.0, 1.0, 0.0, 1.0), vec4(0.0, 0.0, 0.0, 1.0), gradientFactor), vec4(0.0, 1.0 - v_uv.y, 0.0, 1.0), 1.0 - silhouette);
        gl_FragColor = finalColor; 
    }
    
}
