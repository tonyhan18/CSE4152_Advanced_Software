import React from "react";
import styled from "styled-components";

import ChatLogItem from "./ChatLogItem";

function ChatLogTemplate({ chats }) {
  // chats 배열을 받아 저장해 둔 채팅 로그를 보여줌
  // ChatLogItem 컴포넌트 사용
  return (
    <ChatContainer>
      <Title>Chat Log</Title>
      {chats.map((chat) => {
        return <ChatLogItem chat={chat} />;
      })}
    </ChatContainer>
  );
}

const ChatContainer = styled.div`
  width: 500px;
  margin: 10px;
  padding: 20px;
  border-radius: 5px;
  box-shadow: 10px 10px 20px 5px grey;
  background-color: rgb(243, 234, 175);
  // 8주차 실습 구현
`;

const Title = styled.h1`
  margin: 10px;
  padding: 10px;
  border-radius: 5px;

  // 8주차 실습 구현
`;

export default ChatLogTemplate;
