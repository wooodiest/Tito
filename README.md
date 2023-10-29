
# Tito

This is my old physics engine that I created using SDL2. It allows you to simulate a body in a gravitational field. A body is a sphere that has its own mass and radius. It can have its own speed, acceleration and thrust force. It is influenced by gravity and optionally air resistance.

![App Icon](Assetes/Tito.gif)


## Usage
To create a physical object you need to edit function `Engine::AddComponents()` in [Engine.cpp](Tito/src/Core/Engine.cpp)


```cpp
void Engine::AddComponents()
{
	// Adding object example
	GameObjects::GetInstance().Add(
		"sphere1",       /// name
		Color::Pink,	 /// color
		1.0f,            /// mass
		0.1f,            /// radius
		{ 1.0f, 50.0f }, /// position
		{ 0.0f, 0.0f },  /// velocity
		{ 0.0f, 0.0f },  /// acceleration
		{ 0.0f, 0.0f },  /// force
		false	         /// taking air resistance
	);
}
```
- name will be displayed in the logs

- possible colors for the sphere: Blue, Green, Gray, Orange, Pink, Purple, Yellow

- mass, radius, position, velocity, acceleration and force represent the physical properties of a body. They have a value in SI units

- taking air resistance - possible options: true, false

## Build

Clone the repository with `git clone https://github.com/wooodiest/Tito`.

Project tested in Visual Studio 2022. To generate the project run [GenerateProject.bat](GenerateProject.bat)

