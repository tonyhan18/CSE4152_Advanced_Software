import React, { useEffect, useRef, useState } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";

// Sending Message 부분
function MessenagerTemplate({ getChatLog }) {
  const [MsgState, setMsgState] = useState({ message: "", username: "" });
  const ref = useRef();

  const onMsgChange = (e) => {
    const { name, value } = e.target;
    setMsgState({ ...MsgState, [name]: value });
  };

  // 메시지 입력 창에서 빈 경우에는 ‘메시지를 입력하세요‘라는 내용의 경고 창 출력 후 리턴(alert 함수 사용)
  // 사용자의 이름 입력 창이 빈 경우에는 사용자 이름을 ‘이름없음’으로 저장
  // MsgState의 속성(키)들의 값을 빈 문자열로 초기화
  const onMsgSubmit = (e) => {
    e.preventDefault();
    // 8주차 실습 구현
    if (MsgState.message === "") {
      alert("메세지를 입력하세요");
      return;
    }
    if (MsgState.username === "") {
      MsgState.username = "이름없음";
    }
    getChatLog(MsgState.username, MsgState.message);
    setMsgState({ username: "", message: "" });
  };

  const handleKeyPress = (e) => {
    if (e.onKey === "Enter") {
      onMsgSubmit();
    }
  };

  useEffect(() => {
    ref.current.focus();
  }, []);

  return (
    <Form onSubmit={onMsgSubmit}>
      <Title>Sending Message</Title>
      <UserName>
        User Name
        <br />
        <TextField
          ref={ref}
          type="text"
          name="username"
          value={MsgState.username}
          onChange={onMsgChange}
        />
      </UserName>
      <MessageContents>
        Message
        <br />
        <TextField
          ref={ref}
          type="text"
          name="message"
          value={MsgState.message}
          onChange={onMsgChange}
        />
      </MessageContents>
      <Button type="submit" onClick={onMsgSubmit} onKeyPress={handleKeyPress}>
        Send
      </Button>
    </Form>
  );
}

// Sending Message 글씨 박스
const Title = styled.h1`
  margin: 10px;
  padding: 10px;
  border-radius: 5px;
  background-color: rgb(216, 184, 99);
  color: white;
  // 8주차 실습 구현
`;

// 채팅 메시지 입력 form
const Form = styled.form`
  width: 500px;
  margin: 10px;
  padding: 20px;
  border-radius: 5px;
  box-shadow: 10px 10px 20px 5px grey;
  background-color: rgb(255, 253, 228);
  // 8주차 실습 구현
`;

// username 표시
const UserName = styled.div`
  margin: 40px;
`;

// 채팅 메시지 부분
const MessageContents = styled.div`
  margin: 30px;
`;

// send 버튼
const Button = styled.button`
  margin-top: 60px;
  padding: 10px;
  border-radius: 5px;
  border-color: rgb(216, 184, 99);
  background-color: white;
  // 8주차 실습 구현
`;

export default MessenagerTemplate;
