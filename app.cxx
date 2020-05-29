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
