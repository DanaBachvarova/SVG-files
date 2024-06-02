// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"
// #include "circle.hpp"
// #include "figure.hpp"
// #include "SVGParser.hpp"
// #include "point.hpp"
// #include "rect.hpp"
// #include "line.hpp"
// #include "fileManager.hpp"

// #include <string>
// #include <vector>
// #include <cstring>


// TEST_CASE("Splitting input with single token")
// {
//     SVGParser& parser = SVGParser::getInstance();
//     std::string input = "token";
//     parser.splitInput(input);
//     std::vector <std::string> tokens = parser.getTokens();
//     CHECK(tokens.size() == 1);
//     CHECK(tokens[0] == "token");
// }

// TEST_CASE("Splitting input with multiple tokens")
// {
//     SVGParser& parser = SVGParser::getInstance();
//     std::string input = "token1 token2 token3";
//     parser.splitInput(input);
//     std::vector <std::string> tokens = parser.getTokens();
//     CHECK(tokens.size() == 3);
//     CHECK(tokens[0] == "token1");
//     CHECK(tokens[1] == "token2");
//     CHECK(tokens[2] == "token3");
// }

// TEST_CASE("Splitting empty input")
// {
//     SVGParser& parser = SVGParser::getInstance();
//     std::string input = "";
//     parser.splitInput(input);
//     std::vector <std::string> tokens = parser.getTokens();
//     CHECK(tokens.empty());
// }

// TEST_CASE("Circle constructor")
// {
//     SUBCASE("Valid input")
//     {
//         Point center;
//         center.x = 0;
//         center.y = 0;
//         double radius = 5.0;
//         std::string colour = "red";

//         Circle circle(center, radius, colour);

//         CHECK(circle.getCenter().x = center.x && circle.getCenter().y == center.y); 
//         CHECK(circle.getRadius() == radius);
//         CHECK(circle.getColour() == colour);
//     }

//     SUBCASE("Negative radius")
//     {
//         Point center;
//         center.x = 0;
//         center.y = 0;
//         double radius = -5.0;
//         std::string colour = "red";

//         Circle circle(center, radius, colour);

//         CHECK(circle.getCenter().x = center.x && circle.getCenter().y == center.y);
//         CHECK(circle.getRadius() == 0.0); 
//         CHECK(circle.getColour() == colour);
//     }
// }

// TEST_CASE("Rect constructor with valid width and height")
// {
//     Point vertex;
//     vertex.x = 0;
//     vertex.y = 0;
//     double width = 5.0;
//     double height = 3.0;
//     std::string colour = "red";

//     Rect rect(vertex, width, height, colour);

//     CHECK(rect.getVertex().x == vertex.x && rect.getVertex().y == vertex.y);
//     CHECK(rect.getWidth() == width);
//     CHECK(rect.getHeight() == height);
//     CHECK(rect.getColour() == colour);
// }

// TEST_CASE("Rect constructor with negative width")
// {
//     Point vertex;
//     vertex.x = 0;
//     vertex.y = 0;
//     double width = -5.0;
//     double height = 3.0;
//     std::string colour = "red";

//     CHECK_THROWS_AS(Rect rect(vertex, width, height, colour), std::invalid_argument);
// }

// TEST_CASE("Rect constructor with negative height")
// {
//     Point vertex;
//     vertex.x = 0;
//     vertex.y = 0;
//     double width = 5.0;
//     double height = -3.0;
//     std::string colour = "red";

//     CHECK_THROWS_AS(Rect rect(vertex, width, height, colour), std::invalid_argument);
// }

// TEST_CASE("Rect::translate") {
//     Point vertex;
//     vertex.x = 0;
//     vertex.y = 0;
//     double width = 5.0;
//     double height = 3.0;
//     std::string colour = "red";
//     Rect rect(vertex, width, height, colour);

//     double vertical = 2.0;
//     double horizontal = 3.0;
//     rect.translate(vertical, horizontal);

//     CHECK(rect.getVertex().x == vertex.x + horizontal);
//     CHECK(rect.getVertex().y == vertex.y + vertical);
// }

// TEST_CASE("Line translation")
// {
//     Line line({0, 0}, {5, 5}, "black");

//     line.translate(2.5, 2.5);

//     CHECK(line.getStart().x == 2.5);
//     CHECK(line.getStart().y == 2.5);
//     CHECK(line.getEnd().x == 7.5);
//     CHECK(line.getEnd().y == 7.5);
// }

// TEST_CASE("Circle::translate")
// {
//     Circle circle({0, 0}, 5, "red");

//     circle.translate(10, -5);

//     CHECK(circle.getCenter().x == -5);
//     CHECK(circle.getCenter().y == 10);
// }

// TEST_CASE("Test getFiguresFromFile")
// {
//     std::ofstream testFile("test.svg");
//     testFile << "<svg>\n"
//                 "<rect x=\"10\" y=\"20\" width=\"30\" height=\"40\" fill=\"red\" />\n"
//                 "<circle cx=\"50\" cy=\"60\" r=\"70\" fill=\"blue\" />\n"
//                 "<line x1=\"80\" y1=\"90\" x2=\"100\" y2=\"110\" stroke=\"green\" />\n"
//                 "</svg>";
//     testFile.close();

//     std::ifstream inputFile("test.svg");

//     std::vector<Figure*> figures = SVGParser::getInstance().getFiguresFromFile(inputFile);

//     CHECK(figures.size() == 3);

//     CHECK(dynamic_cast<Rect*>(figures[0]) != nullptr);
//     CHECK(dynamic_cast<Circle*>(figures[1]) != nullptr);
//     CHECK(dynamic_cast<Line*>(figures[2]) != nullptr);

//     Rect* rect = dynamic_cast<Rect*>(figures[0]);
//     CHECK(rect->getVertex().x == 10);
//     CHECK(rect->getVertex().y == 20);
//     CHECK(rect->getWidth() == 30);
//     CHECK(rect->getHeight() == 40);

//     Circle* circle = dynamic_cast<Circle*>(figures[1]);
//     CHECK(circle->getCenter().x == 50);
//     CHECK(circle->getCenter().y == 60);
//     CHECK(circle->getRadius() == 70);

//     Line* line = dynamic_cast<Line*>(figures[2]);
//     CHECK(line->getStart().x == 80);
//     CHECK(line->getStart().y == 90);
//     CHECK(line->getEnd().x == 100);
//     CHECK(line->getEnd().y == 110);

//     std::remove("test.svg");
// }

// TEST_CASE("Test getFiguresFromFile")
// {
//     std::ofstream tempFile("test.svg");
//     tempFile << "<svg>\n"
//                 "<rect x=\"10\" y=\"20\" width=\"30\" height=\"40\" fill=\"red\" />\n"
//                 "<circle cx=\"50\" cy=\"60\" r=\"70\" fill=\"blue\" />\n"
//                 "<line x1=\"80\" y1=\"90\" x2=\"100\" y2=\"110\" stroke=\"green\" />\n"
//                 "</svg>";
//     tempFile.close();

//     std::ifstream file("test.svg");

//     std::vector<Figure*> figures = SVGParser::getInstance().getFiguresFromFile(file);

//     CHECK(figures.size() == 3);

//     CHECK(dynamic_cast<Rect*>(figures[0]) != nullptr);
//     CHECK(dynamic_cast<Circle*>(figures[1]) != nullptr);
//     CHECK(dynamic_cast<Line*>(figures[2]) != nullptr);

//     for (Figure* figure : figures)
//     {
//         delete figure;
//     }
// }

// TEST_CASE("Test getFiguresFromFile")
// {
//     std::ofstream tempFile("test.svg");
//     tempFile << "<svg>\n"
//                 "<rect x=\"10\" y=\"20\" width=\"30\" height=\"40\" fill=\"red\" />\n"
//                 "<circle cx=\"50\" cy=\"60\" r=\"70\" fill=\"blue\" />\n"
//                 "<line x1=\"80\" y1=\"90\" x2=\"100\" y2=\"110\" stroke=\"green\" />\n"
//                 "</svg>";
//     tempFile.close();

//     std::ifstream file("test.svg");

//     std::vector<Figure *> figures = SVGParser::getInstance().getFiguresFromFile(file);

//     CHECK(figures.size() == 3);

//     CHECK(dynamic_cast<Rect *>(figures[0]) != nullptr);
//     CHECK(dynamic_cast<Circle *>(figures[1]) != nullptr);
//     CHECK(dynamic_cast<Line *>(figures[2]) != nullptr);

//     Rect *rect = dynamic_cast<Rect *>(figures[0]);
//     CHECK(rect->getVertex().x == 10);
//     CHECK(rect->getVertex().y == 20);
//     CHECK(rect->getWidth() == 30);
//     CHECK(rect->getHeight() == 40);

//     Circle *circle = dynamic_cast<Circle *>(figures[1]);
//     CHECK(circle->getCenter().x == 50);
//     CHECK(circle->getCenter().y == 60);
//     CHECK(circle->getRadius() == 70);

//     Line *line = dynamic_cast<Line *>(figures[2]);
//     CHECK(line->getStart().x == 80);
//     CHECK(line->getStart().y == 90);
//     CHECK(line->getEnd().x == 100);
//     CHECK(line->getEnd().y == 110);

//     for (Figure *figure : figures)
//     {
//         delete figure;
//     }
//     file.close();
//     std::remove("test.svg");
// }

// TEST_CASE("Test getFiguresFromFile")
// {
//     SVGParser& parser = SVGParser::getInstance();
//     std::ifstream file("test.svg");
//     std::vector<Figure*> figures = parser.getFiguresFromFile(file);

//     CHECK(figures.size() == 3);

//     Rect* rect = dynamic_cast<Rect*>(figures[0]);
//     CHECK(rect != nullptr);
//     CHECK(rect->getWidth() == 10.0);
//     CHECK(rect->getHeight() == 20.0);
//     CHECK(rect->getColour() == "red");

//     Circle* circle = dynamic_cast<Circle*>(figures[1]);
//     CHECK(circle != nullptr);
//     CHECK(circle->getRadius() == 5.0);
//     CHECK(circle->getColour() == "blue");

//     Line* line = dynamic_cast<Line*>(figures[2]);
//     CHECK(line != nullptr);
//     CHECK(line->getStart().x == 0.0);
//     CHECK(line->getStart().y == 0.0);
//     CHECK(line->getEnd().x == 10.0);
//     CHECK(line->getEnd().y == 10.0);
//     CHECK(line->getColour() == "black");
// }

// TEST_CASE("Test getFigureFromStr")
// {
//     SVGParser& parser = SVGParser::getInstance();

//     Figure* rectFigure = parser.getFigureFromStr("<rect x=\"0\" y=\"0\" width=\"10\" height=\"20\" fill=\"red\" />");
//     Rect* rect = dynamic_cast<Rect*>(rectFigure);
//     CHECK(rect != nullptr);
//     CHECK(rect->getWidth() == 10.0);
//     CHECK(rect->getHeight() == 20.0);

//     Figure* circleFigure = parser.getFigureFromStr("<circle cx=\"5\" cy=\"5\" r=\"5\" fill=\"blue\" />");
//     Circle* circle = dynamic_cast<Circle*>(circleFigure);
//     CHECK(circle != nullptr);
//     CHECK(circle->getRadius() == 5.0);

//     Figure* lineFigure = parser.getFigureFromStr("<line x1=\"0\" y1=\"0\" x2=\"10\" y2=\"10\" stroke=\"black\" />");
//     Line* line = dynamic_cast<Line*>(lineFigure);
//     CHECK(line != nullptr);
//     CHECK(line->getStart().x == 0.0);
//     CHECK(line->getStart().y == 0.0);
//     CHECK(line->getEnd().x == 10.0);
//     CHECK(line->getEnd().y == 10.0);
// }

// TEST_CASE("Line::withinRect")
// {
//     Line line1({2.0, 3.0}, {4.0, 5.0}, "black");
//     CHECK(line1.withinRect(1.0, 2.0, 5.0, 6.0) == true);

//     Line line2({6.0, 7.0}, {8.0, 9.0}, "red");
//     CHECK(line2.withinRect(1.0, 2.0, 5.0, 6.0) == false);

//     Line line3({10.0, 11.0}, {12.0, 13.0}, "blue");
//     CHECK(line3.withinRect(1.0, 2.0, 5.0, 6.0) == false);
// }

// TEST_CASE("Line::withinCircle")
// {
//     Line line({0, 0}, {3, 4}, "black");

//     CHECK(line.withinCircle(0, 0, 5) == true);

//     CHECK(line.withinCircle(0, 0, 3) == true);

//     CHECK(line.withinCircle(0, 0, 2) == false);
// }

// TEST_CASE("Rect::withinRect")
// {
//     Rect rect({0, 0}, 10, 10, "red");

//     CHECK(rect.withinRect(0, 0, 20, 20) == true);
//     CHECK(rect.withinRect(5, 5, 10, 10) == true);
//     CHECK(rect.withinRect(15, 15, 10, 10) == false);
//     CHECK(rect.withinRect(-5, -5, 10, 10) == false);
// }

// TEST_CASE("Circle::withinRect")
// {
//     Circle circle({0, 0}, 5, "red");

//     CHECK(circle.withinRect(-10, -10, 20, 20) == true);
//     CHECK(circle.withinRect(-5, -5, 10, 10) == true);
//     CHECK(circle.withinRect(5, 5, 10, 10) == false);
//     CHECK(circle.withinRect(-15, -15, 10, 10) == false);
// }

// TEST_CASE("Circle::withinRect - Additional Test Cases")
// {
//     Circle circle({0, 0}, 10, "blue");

//     CHECK(circle.withinRect(-10, -10, 10, 10) == true);
//     CHECK(circle.withinRect(-5, -5, 5, 5) == true);
//     CHECK(circle.withinRect(10, 10, 5, 5) == false);
//     CHECK(circle.withinRect(-15, -15, 5, 5) == false);
// }

// TEST_CASE("FileManager::openFile")
// {
//     FileManager& fileManager = FileManager::getInstance();

//     SUBCASE("Open existing file")
//     {
//         std::string filePath = "existing_file.svg";
//         CHECK(fileManager.openFile(filePath) == true);
//         CHECK(fileManager.getFileLoaded() == true);
//     }

//     SUBCASE("Open non-existing file")
//     {
//         std::string filePath = "non_existing_file.svg";
//         CHECK(fileManager.openFile(filePath) == true);
//         CHECK(fileManager.getFileLoaded() == true);
//     }
// }