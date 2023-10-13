#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform bool explode;
uniform float timeE;



// Output
out vec2 texcoord;
out float noise;


float turbulence( vec3 p ) {

  float w = 100.0;
  float t = -.5;

  for (float f = 1.0 ; f <= 10.0 ; f++ ){
    float power = pow( 2.0, f );
    t += abs( noise1( vec3( power * p ) ) / power );
  
  }

  return t;

}

void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;
    if(explode == true){
    // get a turbulent 3d noise using the normal, normal to high freq
    noise = 5.0 * -.10 * turbulence( .5 * v_normal );
    // get a 3d noise using the position, low frequency
    float b = noise1( timeE * v_position + timeE/100);//, vec3( 100.0 ) );

    // compose both noises
    float displacement = - timeE * noise + b;

    // move the position along the normal and transform it
    vec3 newPosition = v_position + v_normal * displacement;

    gl_Position = Projection * View * Model * vec4(newPosition, 1.0);
    }else{
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
    }
}
