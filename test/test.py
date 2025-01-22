import requests
from concurrent.futures import ThreadPoolExecutor, as_completed

TEST_URL = "http://localhost:8080/tasks/add"

def make_request(data):
    try:
        response = requests.post(TEST_URL, json=data)
        return {"status_code": response.status_code, "response": response.json}
    except Exception as e:
        return {"error": str(e)}
    
def test_requests_multithreaded():
    payloads = [{'name': f'Task {i}', 'priority': 'High', 'hours': i} for i in range(1, 20000)]

    results = []

    max_threads = 20

    with ThreadPoolExecutor(max_workers=max_threads) as executor:
        future_to_payload = {executor.submit(make_request, payload): payload for payload in payloads}

        for future in as_completed(future_to_payload):
            payload = future_to_payload[future]
            try:
                result = future.result()
                results.append(result)
                print(f"Payload: {payload}, Result: {result}")
            except Exception as exc:
                print(f"Payload {payload} generated an exception: {exc}")

    # Проверяем, что все запросы успешны
    for i, result in enumerate(results, 1):
        assert result.get("status_code") == 201, f"Request {i} failed: {result}"

if __name__ == "__main__":
    test_requests_multithreaded()