//------------------------------------------------------------------------------
// From http://github.com/heitorperalles/checkCpfCxx
//
// Distributed under The MIT License (MIT) <http://opensource.org/licenses/MIT>
//
// Copyright (c) 2020 Heitor Peralles <heitorgp@gmail.com>
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------
#include "middleware.hxx"

// Messages to returned
#define REGULAR_MESSAGE 							"Regular CPF (OK)" // status 200
#define INVALID_CPF_FORMAT_MESSAGE		"Invalid CPF format" // status 400
#define SUBJECT_REJECTED_MESSAGE			"CPF not regular or not existant" // status 403
#define EXTERNAL_SERVER_ERROR_MESSAGE "Server communication problem" // status 500
#define UNKNOWN_ERROR_MESSAGE 				"Unknown error" // another status code
#define INVALID_PARAMETER_MESSAGE 		"Invalid arguments, call with 1 and only 1 CPF" // bad arguments

/**
 * Program entry point.
 */
int main(int argc, char **argv) {

	if (argc != 2) {
		printf("CPF:      ?\n");
		printf("SUCCESS:  False\n");
		printf("MESSAGE:  %s\n", INVALID_PARAMETER_MESSAGE);
		return 1;
	}

	printf("CPF:     %s\n", argv[1]);
	auto cpfValidationCode = Middleware::validateCpf(argv[1]);
	const char * status;
	const char * message;
	switch (cpfValidationCode) {
		case 200:
			status = "True";
			message = REGULAR_MESSAGE;
			break;
		case 403:
			status = "False";
			message = SUBJECT_REJECTED_MESSAGE;
			break;
		case 400:
			status = "False";
			message = INVALID_CPF_FORMAT_MESSAGE;
			break;
		case 500:
			status = "False";
			message = EXTERNAL_SERVER_ERROR_MESSAGE;
			break;
		default:
			status = "False";
			message = UNKNOWN_ERROR_MESSAGE;
			break;
	};
	printf("SUCCESS: %s\n", status);
	printf("MESSAGE: %s\n", message);

  return 0;
}
