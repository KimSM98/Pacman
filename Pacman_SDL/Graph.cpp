#include "Graph.h"
#include "Actor.h"
#include <fstream>
#include <iostream>
#include <string>

Graph::Graph(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, _DistanceBetweenNodes(0)
	, _AllowsDrawing(false)
{
}

Graph::~Graph()
{
	for (auto v : _Nodes)
	{
		for (auto n : v)
		{
			delete n;
		}
	}
}

void Graph::Draw(SDL_Renderer* renderer)
{
	if (_AllowsDrawing)
	{
		for (auto v : _Nodes)
		{
			for (auto n : v)
			{
				if (n != nullptr)
				{
					n->Draw(renderer);
				}
			}
		}
	}
}


Node* Graph::GetNode(int row, int column) 
{
	return _Nodes[row][column];
}

int Graph::SetGraphStateFromFile(std::string fileName)
{
	// file �ҷ�����
	std::ifstream input((fileName));

	if (input.fail())
	{
		std::cout << "File Name : " << fileName << " does not exist." << '\n';
		return 0;
	}

	// file �б�
	std::string dataFromFile;
	std::string temp;
	int i(0), j(0);

	Vector2 actorPos = _Owner->GetPosition();

	while (getline(input, dataFromFile)) // ���Ͱ� ������ �������� string���� �޴´�.
	{
		std::vector<Node*> vec;
		Vector2 nodePos;
		// ','�� �������� ���� �ڸ���.
		for (int n = 0; n < dataFromFile.length(); n++)
		{
			if (dataFromFile[n] == ',')
			{
				if (std::stoi(temp) == 0)
				{
					vec.push_back(nullptr);
				}
				else // 0�� �ƴϸ� ��� ����
				{
					nodePos.x = (actorPos.x + _DistanceBetweenNodes * j) + _DistanceBetweenNodes / 2;
					nodePos.y = (actorPos.y + _DistanceBetweenNodes * i + _DistanceBetweenNodes / 2);

					vec.push_back(new Node(nodePos, _DistanceBetweenNodes));
				}

				temp.clear();
				j++;
			}
			else if (dataFromFile[n] != ',')
				temp += dataFromFile[n];
		}
		// ','�� ���� ������ ������  
		if (std::stoi(temp) == 0)
		{
			vec.push_back(nullptr);
		}
		else // 0�� �ƴϸ� ��� ����
		{
			nodePos.x = (actorPos.x + _DistanceBetweenNodes * j) + _DistanceBetweenNodes / 2;
			nodePos.y = (actorPos.y + _DistanceBetweenNodes * i + _DistanceBetweenNodes / 2);

			vec.push_back(new Node(nodePos, _DistanceBetweenNodes));
		}

		temp.clear();
		i++;
		j = 0;

		_Nodes.push_back(vec);
	}
	SDL_Log("Graph creation completed.");

	ArrangeAdjNodes();

	_AllowsDrawing = true;
}

void Graph::PrintNodes()
{
	for (auto v : _Nodes)
	{
		for (auto n : v)
		{
			if (n != nullptr)
				std::cout << " 1 ";
			else if (n == nullptr)
				std::cout << " 0 ";
		}
		std::cout << '\n';
	}
}

void Graph::ArrangeAdjNodes()
{
	int row = _Nodes.size();
	int column = _Nodes.front().size();

	// ���� ����� ������, �Ʒ��� Ž��
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = 0; j < column - 1; j++)
		{
			if (_Nodes[i][j] != nullptr)
			{
				if (_Nodes[i][j + 1] != nullptr) // ���� ����� ������ ��� ���� ���� Ȯ��
				{
					_Nodes[i][j]->AddAdjNode(Direction::Right, _Nodes[i][j + 1]);
					_Nodes[i][j + 1]->AddAdjNode(Direction::Left, _Nodes[i][j]);
				}
				if (_Nodes[i + 1][j] != nullptr) // ���� ����� �Ʒ��� ��� ���� ���� Ȯ��
				{
					_Nodes[i][j]->AddAdjNode(Direction::Bottom, _Nodes[i + 1][j]);
					_Nodes[i + 1][j]->AddAdjNode(Direction::Top, _Nodes[i][j]);
				}
			}
		}
	}
	std::cout<<std::endl;
	
	// �׷����� ������ row nodes
	for (int j = 0; j < column - 1; j++)
	{
		if (_Nodes[row - 1][j])
		{
			// �ش� ����� ������ Ž��
			if (_Nodes[row - 1][j + 1])
			{
				_Nodes[row - 1][j]->AddAdjNode(Direction::Right, _Nodes[row - 1][j + 1]);
				_Nodes[row - 1][j + 1]->AddAdjNode(Direction::Left, _Nodes[row - 1][j]);
			}
		}
	}
	// �׷����� ������ column nodes
	for (int i = 0; i < row - 1; i++)
	{
		if (_Nodes[i][column - 1])
		{
			if (_Nodes[i + 1][column - 1])
			{
				_Nodes[i][column - 1]->AddAdjNode(Direction::Bottom, _Nodes[i + 1][column - 1]);
				_Nodes[i + 1][column - 1]->AddAdjNode(Direction::Top, _Nodes[i][column - 1]);
			}
		}
	}
	std::cout << "���� �Ϸ�" << '\n';
}